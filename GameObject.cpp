#include "LevelManager.h"
#include "GameObject.h"
#include <iostream>
#include "gameSettings.h"

void GameObject::Init()
{
	// noop
}

void GameObject::Update(Uint64 delta) {
	MoveBy(velocity * speed * delta);
}

void GameObject::Draw(SDL_Renderer* renderer) const
{
	RGBColor drawColor = DEBUG_MODE ? COLOR_RED : color;
	auto drawRect = GetBounds();
	SDL_SetRenderDrawColor(renderer, drawColor.R, drawColor.G, drawColor.B, drawColor.A);
	SDL_RenderPoint(renderer, position.X, position.Y);
	if (DEBUG_MODE) {
		SDL_RenderRect(renderer, &drawRect);
	}
	else {
		SDL_RenderFillRect(renderer, &drawRect);
	}

	DrawCollider(renderer);
}

void GameObject::DrawCollider(SDL_Renderer* renderer) const
{
	if (SETTINGS::SHOW_COLLIDERS) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 155);
		for (auto& collider : colliders) {
			if (collider->IsTrigger() && SETTINGS::SHOW_COLLIDER_MODE == 1) {
				auto triggerRect = collider->GetBounds();
				SDL_RenderRect(renderer, &triggerRect);
			}
			if (!collider->IsTrigger() && SETTINGS::SHOW_COLLIDER_MODE == 0) {
				auto colliderRect = collider->GetBounds();
				SDL_RenderRect(renderer, &colliderRect);
			}
		}
	}
}

void GameObject::SetVelocityX(float x)
{
	velocity.X = x;
	velocity.Normalize();
}

void GameObject::SetVelocityY(float y)
{
	velocity.Y = y;
	velocity.Normalize();
}

void GameObject::MoveTo(float x, float y)
{
	position.X = x;
	position.Y = y;
	BoundPositionToScreenSize();
}

void GameObject::MoveTo(vector2 vec)
{
	position.X = vec.X;
	position.Y = vec.Y;
	BoundPositionToScreenSize();
}

void GameObject::MoveBy(float x, float y) {
	position.X += x;
	position.Y += y;
	BoundPositionToScreenSize();
}

void GameObject::MoveBy(vector2 vec) {
	position.X += vec.X;
	position.Y += vec.Y;
	BoundPositionToScreenSize();
}

SDL_FRect GameObject::GetBounds() const
{
	SDL_FRect rect;
	rect.x = position.X - size.X / 2;
	rect.y = position.Y - size.Y / 2;
	rect.w = size.X;
	rect.h = size.Y;
	return rect;
}

void GameObject::BoundPositionToScreenSize() {
	auto size2 = size / 2;
	if (position.X + size2.X > GAME_WINDOW_SIZE) {
		position.X = GAME_WINDOW_SIZE - size2.X;
	}
	if (position.X - size2.X < 0) {
		position.X = size2.X;
	}

	if (position.Y + size2.Y > GAME_WINDOW_SIZE) {
		position.Y = GAME_WINDOW_SIZE - size2.Y;
	}
	if (position.Y - size2.Y < 0) {
		position.Y = size2.Y;
	}
}

CollisionComponent* GameObject::AddCollider(vector2 bounds)
{
	auto collider = std::make_shared<CollisionComponent>();
	collider->SetOwner(this);
	collider->SetBounds(bounds);
	colliders.push_back(collider);
	return collider.get();
}

CollisionComponent* GameObject::AddCollider(vector2 bounds, ECollisionLayer layer)
{
	auto collider = AddCollider(bounds);
	collider->SetLayer(layer);
	return collider;
}
