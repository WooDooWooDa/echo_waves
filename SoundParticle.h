#pragma once
#include "GameObject.h"
#include <SDL3/SDL_stdinc.h>
//#include <queue>

class SoundParticle : public GameObject
{
private:
	/*float distanceBetweenTrailPoint = LEVEL_TILE_SIZE / 10;
	float distanceMoved = 0.0;
	const int maxTrailLength = 20;
	std::queue<vector2> trailPoints;*/

	float ttl = 0.0;
	float currentTTL = 0.0;
	float maxSpeed = 5;

public:
	SoundParticle(float ttl, vector2 pos, vector2 dir, float spd) : GameObject() {
		name = "SoundParticle";
		size = LEVEL_TILE_SIZE / 10;
		this->ttl = ttl;
		currentTTL = ttl;
		position = pos;
		velocity = dir;
		maxSpeed = spd;
		speed = maxSpeed;
		color = COLOR_WHITE;
		AddCollider(size, ECollisionLayer::LSoundParticle);

		//trailPoints.push(pos);
	}

	void Draw(SDL_Renderer*) const override;
	void Update(Uint64 delta) override;

	void OnCollisionEnter(CollisionResult) override;
private:
	//void AddTrailPoint(vector2);
};

