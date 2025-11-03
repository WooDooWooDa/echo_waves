#include "GameObject.h"
#include <iostream>

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
}

void GameObject::Move(vector2 vec) {
	position.X += vec.X;
	position.Y += vec.Y;
}