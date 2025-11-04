#include "CollisionSystem.h"
#include "CollisionResult.h"

void CollisionSystem::CheckCollision(std::shared_ptr<Level> currentLevel)
{
    if (!isInit) InitCollisionMatrix();

    auto objs = currentLevel->GetAllGameObjects();
    for (auto& a : objs) {
        for (auto& b : objs) {
            if (a == b) continue;

            CollisionComponent collider = a->GetCollider();
            if (!ShouldCollide(collider.GetLayer(), b.get()->GetCollider().GetLayer())) continue;

            SDL_FRect intersectResult;
            if (collider.IsTrigger() && collider.Intersects(*b, intersectResult)) {
                a->OnTriggerEnter(b.get());
            } else if (collider.IsCollisionEnable() && collider.Intersects(*b, intersectResult)) {
                CollisionResult collisionResult;
                collisionResult.intersect = intersectResult;
                collisionResult.other = b.get();
                ResolveCollision(*a, collisionResult);
                a->OnCollisionEnter(collisionResult);
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
}
