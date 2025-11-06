#include "SoundParticle.h"
#include <iostream>

float lerp(float a, float b, float f) {
	return a + f * (b - a);
}

void SoundParticle::Update(Uint64 delta)
{
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
	currentTTL /= 2;
	collision.collisionNormal.Normalize();
	velocity = velocity - collision.collisionNormal * (2 * (velocity.dot(collision.collisionNormal)));
}
