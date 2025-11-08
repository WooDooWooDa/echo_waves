#include "CollisionSystem.h"
#include "CollisionResult.h"

void CollisionSystem::CheckCollision(Level* currentLevel)
{
    std::unordered_map<CollisionComponent*, std::unordered_set<GameObject*>> newOverlaps;
    auto objs = currentLevel->GetAllGameObjects();

    //Test all obj colliders against all obj colliders
    for (auto& a : objs) {
        if (a->IsDestroyed()) continue;
        auto colliders = a->GetColliders();
        for (auto& collider : colliders) {
            if (!collider->IsCollisionEnable()) continue;

            for (auto& b : objs) {
                if (b->IsDestroyed()) continue;
                if (a == b) continue;

                auto bColliders = b->GetColliders();
                for (auto& bCollider : bColliders) {
                    if (!bCollider->IsCollisionEnable()) continue;
                    if (!ShouldCollide(collider->GetLayer(), bCollider->GetLayer())) continue;

                    SDL_FRect intersectResult;
                    // Handle trigger Enter
                    if ((collider->IsTrigger() || bCollider->IsTrigger()) && collider->Intersects(*bCollider, intersectResult)) {
                        newOverlaps[collider.get()].insert(b.get());
                        
                        if (!collider->IsOverlapping(b.get())) {
                            a->OnTriggerEnter(b.get());
                            collider->RegisterOverlap(b.get());
                        }
                    }
                    // Handle Collision Enter
                    else if (collider->Intersects(*bCollider, intersectResult)) {
                        CollisionResult collisionResult;
                        collisionResult.intersect = intersectResult;
                        collisionResult.other = b.get();
                        ResolveCollision(*a, collisionResult);
                        a->OnCollisionEnter(collisionResult);
                    }
                }
            }
        }
    }

    //Handle trigger exit
    for (auto& obj : objs) {
        auto colliders = obj->GetColliders();
        for (auto& collider : colliders) {
            std::unordered_set<GameObject*> currentFrameOverlaps;
            
            // Get currentFrameOverlap of this collider, if any
            auto found = newOverlaps.find(collider.get());
            if (found != newOverlaps.end()) {
                currentFrameOverlaps = found->second;
            }
            // Get collider previous overlaps
            auto& prevOverlaps = collider->GetCurrentOverlaps();
            // Do nothing if sets are still equal, same overlaps
            if (prevOverlaps == currentFrameOverlaps) continue;
            // Call onExit on previous overlaps not overlapping this frame
            for (auto* prev : prevOverlaps) {
                if (currentFrameOverlaps.find(prev) == currentFrameOverlaps.end()) {
                    collider->OnTriggerExit(prev);
                }
            }
            //Update collider current overlaps (via ref)
            collider->GetCurrentOverlaps() = currentFrameOverlaps;
        }
    }
}

void CollisionSystem::ResolveCollision(GameObject& go, CollisionResult& res)
{
    auto goPosition = go.GetPosition();
    auto intersect = res.intersect;
    if (intersect.w < intersect.h) {
        if (goPosition.X < intersect.x + intersect.w / 2) {
            go.MoveTo(goPosition.X - intersect.w, goPosition.Y);
            res.collisionNormal = vector2(-1, 0);
        }
        else {
            go.MoveTo(goPosition.X + intersect.w, goPosition.Y);
            res.collisionNormal = vector2(1, 0);
        }
    }
    else {
        if (goPosition.Y < intersect.y + intersect.h / 2) {
            go.MoveTo(goPosition.X, goPosition.Y - intersect.h);
            res.collisionNormal = vector2(0, -1);
        }
        else {
            go.MoveTo(goPosition.X, go.GetPosition().Y + intersect.h);
            res.collisionNormal = vector2(0, 1);
        }
    }

    res.hitPosition = vector2(
        intersect.x + intersect.w * 0.5f,
        intersect.y + intersect.h * 0.5f
    ) - res.collisionNormal * 0.5f * std::min(intersect.w, intersect.h);
}
