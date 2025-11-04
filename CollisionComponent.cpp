#include "CollisionComponent.h"
#include <SDL3/SDL_rect.h>
#include "GameObject.h"  // now we include the full definition

void CollisionComponent::OnTriggerEnter(GameObject* other)
{
	owner->OnTriggerEnter(other);
}

void CollisionComponent::OnCollisionEnter(CollisionResult res)
{
	owner->OnCollisionEnter(res);
}

bool CollisionComponent::Intersects(const GameObject& other, SDL_FRect& intersectResult)
{
	auto owRect = owner->GetBounds();
	auto otRect = other.GetBounds();
	return SDL_GetRectIntersectionFloat(&owRect, &otRect, &intersectResult);
}
