#include "GameObject.h"
#include <iostream>
#include "gameSettings.h"

void GameObject::Update(Uint64 delta) {
	Move(velocity * speed * delta);
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

void GameObject::Move(float x, float y) {
	position.X += x;
	position.Y += y;
	BoundPositionToScreenSize();
}

void GameObject::Move(vector2 vec) {
	position.X += vec.X;
	position.Y += vec.Y;
	BoundPositionToScreenSize();
}

void GameObject::BoundPositionToScreenSize() {
	float size2 = size / 2;
	if (position.X + size2 > GAME_WINDOW_WIDTH) {
		position.X = GAME_WINDOW_WIDTH - size2;
	}
	if (position.X - size2 < 0) {
		position.X = size2;
	}

	if (position.Y + size2 > GAME_WINDOW_HEIGHT) {
		position.Y = GAME_WINDOW_HEIGHT - size2;
	}
	if (position.Y - size2 < 0) {
		position.Y = size2;
	}
}