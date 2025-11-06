#pragma once
#include "GameObject.h"
#include <SDL3/SDL_stdinc.h>

class SoundParticle : public GameObject
{
private:
	float ttl = 0.0;
	float currentTTL = 0.0;
	float maxSpeed = 5;

public:
	SoundParticle(float ttl, vector2 pos, vector2 dir) : GameObject() {
		size = LEVEL_TILE_SIZE / 10;
		this->ttl = ttl;
		currentTTL = ttl;
		position = pos;
		velocity = dir;
		speed = maxSpeed;
		color = COLOR_WHITE;
		collision.SetLayer(ECollisionLayer::LSoundParticle);
	}

	void Update(Uint64 delta) override;

	void OnCollisionEnter(CollisionResult) override;
};

