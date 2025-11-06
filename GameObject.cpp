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
	if (DEBUG_MODE) {
		SDL_RenderRect(renderer, &drawRect);
	}
	else {
		SDL_RenderFillRect(renderer, &drawRect);
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
	rect.x = position.X - size / 2;
	rect.y = position.Y - size / 2;
	rect.w = rect.h = size;
	return rect;
}

void GameObject::BoundPositionToScreenSize() {
	float size2 = size / 2;
	if (position.X + size2 > GAME_WINDOW_SIZE) {
		position.X = GAME_WINDOW_SIZE - size2;
	}
	if (position.X - size2 < 0) {
		position.X = size2;
	}

	if (position.Y + size2 > GAME_WINDOW_SIZE) {
		position.Y = GAME_WINDOW_SIZE - size2;
	}
	if (position.Y - size2 < 0) {
		position.Y = size2;
	}
}