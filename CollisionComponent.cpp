#include "CollisionComponent.h"
#include <SDL3/SDL_rect.h>
#include "GameObject.h"  // now we include the full definition

SDL_FRect CollisionComponent::GetBounds() const
{
	auto pos = owner->GetPosition();
	SDL_FRect rect = { pos.X - bounds.X / 2, pos.Y - bounds.Y / 2, bounds.X, bounds.Y };
	return rect;
}

void CollisionComponent::OnTriggerEnter(GameObject* other)
{
	owner->OnTriggerEnter(other);
}

void CollisionComponent::OnTriggerStay(GameObject* other)
{
	owner->OnTriggerStay(other);
}

void CollisionComponent::OnTriggerExit(GameObject* other)
{
	owner->OnTriggerExit(other);
}

void CollisionComponent::OnCollisionEnter(CollisionResult res)
{
	owner->OnCollisionEnter(res);
}

bool CollisionComponent::Intersects(const CollisionComponent& other, SDL_FRect& intersectResult)
{
	auto owRect = GetBounds();
	auto otRect = other.GetBounds();
	return SDL_GetRectIntersectionFloat(&owRect, &otRect, &intersectResult);
}
