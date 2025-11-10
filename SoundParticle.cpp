#include "SoundParticle.h"
#include <iostream>
#include "math.h"
#include "LevelManager.h"

void SoundParticle::Draw(SDL_Renderer* renderer) const
{
	GameObject::Draw(renderer);
	//Draw lines, last point is particle position
	/*for (size_t i = 0; i < trailPoints.size() - 1; i++)
	{
		SDL_RenderLine(renderer, );
	}*/
}

void SoundParticle::Update(Uint64 delta)
{
	auto lastPos = position;
	GameObject::Update(delta);

	/*auto posDiff = lastPos - position;
	if (posDiff.Length() > 0) {
		distanceMoved += posDiff.Length();
	}

	if (distanceMoved > distanceBetweenTrailPoint) {
		AddTrailPoint(position);
		distanceMoved = 0;
	}*/

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

	
	//AddTrailPoint(position);
	//distanceMoved = 0;
}

/*void SoundParticle::AddTrailPoint(vector2 point)
{
	if (trailPoints.size() >= maxTrailLength) {
		trailPoints.pop();
	}
	trailPoints.push(point);
}*/
