#include "SoundParticle.h"
#include <iostream>
#include "math.h"
#include "LevelManager.h"

void SoundParticle::Draw(SDL_Renderer* renderer) const
{
	GameObject::Draw(renderer);
}

void SoundParticle::Update(Uint64 delta)
{
	auto lastPos = position;
	GameObject::Update(delta);

	currentTTL -= delta;
	speed = lerp(0, maxSpeed, currentTTL / ttl);
	color.A = lerp(0, 255, currentTTL / ttl);

	if (currentTTL <= 0) {
		Destroy();
	}
}

void SoundParticle::OnCollisionEnter(CollisionResult collision)
{
	if (collision.other == emitter) return;

	currentTTL /= 2;
	collision.collisionNormal.Normalize();
	velocity = velocity - collision.collisionNormal * (2 * (velocity.dot(collision.collisionNormal)));
}
