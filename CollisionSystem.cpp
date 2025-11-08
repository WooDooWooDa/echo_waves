#include "CollisionSystem.h"
#include "CollisionResult.h"

void CollisionSystem::CheckCollision(Level* currentLevel)
{
    auto objs = currentLevel->GetAllGameObjects();
    for (auto& a : objs) {
        auto colliders = a->GetColliders();
        for (auto& collider : colliders) {
            if (!collider->IsCollisionEnable()) continue;

            for (auto& b : objs) {
                if (a == b) continue;

                auto bColliders = b->GetColliders();
                for (auto& bCollider : bColliders) {
                    if (!ShouldCollide(collider->GetLayer(), bCollider->GetLayer())) continue;

                    SDL_FRect intersectResult;
                    if (collider->IsTrigger() && collider->Intersects(*bCollider, intersectResult)) {
                        a->OnTriggerEnter(b.get());
                    }
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
