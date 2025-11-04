#include "CollisionSystem.h"
#include <shared_mutex>

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
                ResolveCollision(*a, intersectResult);
                a->OnCollisionEnter(b.get());
            }
        }
    }
}

void CollisionSystem::ResolveCollision(GameObject& go, SDL_FRect& intersect)
{
    auto goPosition = go.GetPosition();
    if (intersect.w < intersect.h) {
        if (goPosition.X < intersect.x + intersect.w / 2) {
            go.MoveTo(goPosition.X - intersect.w, goPosition.Y);
        }
        else {
            go.MoveTo(goPosition.X + intersect.w, goPosition.Y);
        }
        go.SetVelocityX(0);
    }
    else {
        if (goPosition.Y < intersect.y + intersect.h / 2) {
            go.MoveTo(goPosition.X, goPosition.Y - intersect.h);
        }
        else {
            go.MoveTo(goPosition.X, go.GetPosition().Y + intersect.h);
        }
        go.SetVelocityY(0);
    }
}
