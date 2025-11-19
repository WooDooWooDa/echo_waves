#include "CollisionSystem.h"
#include "CollisionResult.h"
#include "SoundParticle.h"
#include "Level.h"

void CollisionSystem::CheckCollision(Level* currentLevel)
{
    std::unordered_map<CollisionComponent*, std::unordered_set<GameObject*>> newOverlaps;
    auto& objs = currentLevel->GetAllGameObjects();

    //Test all obj colliders against all NEAR objs
    for (auto& A : objs) {
        auto a = A.get();
        if (a->IsDestroyed()) continue;
        //std::vector<GameObject*> nearObjs;
        //currentLevel->GetGrid().Query(a, nearObjs);

        //if (nearObjs.empty()) continue;

        auto& aColliders = a->GetColliders();
        for (auto& aCollider : aColliders) {
            if (aCollider->GetCollisionType() == STATIC || !aCollider->IsCollisionEnable()) continue;

            for (auto& B : objs) {//nearObjs) {
                auto b = B.get();
                if (b->IsDestroyed() || a == b) continue;

                // Skip collision for a soundParticle's emitter
                if (a->name == "SoundParticle" && b == ((SoundParticle*)a)->emitter)
                    continue;
                if (b->name == "SoundParticle" && a == ((SoundParticle*)b)->emitter)
                    continue;

                auto& bColliders = b->GetColliders();
                for (auto& bCollider : bColliders) {
                    if (!bCollider->IsCollisionEnable()) continue;

                    SDL_FRect intersectResult;
                    bool hasIntersection = aCollider->Intersects(*bCollider, intersectResult);
                    if (!hasIntersection) continue;
                    // Handle trigger Enter
                    if ((aCollider->IsTrigger() || bCollider->IsTrigger())) {
                        newOverlaps[aCollider.get()].insert(b);
                        newOverlaps[bCollider.get()].insert(a);

                        if (!aCollider->IsOverlapping(b)) {
                            a->OnTriggerEnter(b);
                            aCollider->RegisterOverlap(b);
                        }
                        else if (bCollider->IsOverlapping(a)) {
                            b->OnTriggerEnter(a);
                            bCollider->RegisterOverlap(a);
                        }

                        continue;
                    }

                    if (!ShouldCollide(aCollider->GetLayer(), bCollider->GetLayer())) continue;

                    // Handle Collision Enter
                    CollisionResult collisionResult;
                    collisionResult.intersect = intersectResult;
                    collisionResult.other = b;
                    ResolveCollision(*a, collisionResult);
                    a->OnCollisionEnter(collisionResult);
                    collisionResult.other = a;
                    b->OnCollisionEnter(collisionResult);
                }
            }
        }
    }

    //Handle trigger exit & stay
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
            // Do nothing if sets are still equal, trigger stay on prevs
            if (prevOverlaps == currentFrameOverlaps) {
                for (auto* prev : prevOverlaps) {
                    collider->OnTriggerStay(prev);
                }
                continue;
            }
            // Call onExit on previous overlaps not overlapping this frame
            for (auto* prev : prevOverlaps) {
                if (currentFrameOverlaps.find(prev) == currentFrameOverlaps.end()) {
                    collider->OnTriggerExit(prev);
                }
                else {
                    collider->OnTriggerStay(prev);
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
