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
	GameObject* emitter;

	SoundParticle(float ttl, vector2 pos, vector2 dir, float spd) : GameObject() {
		shouldCache = false;
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
	}

	void Draw(SDL_Renderer*) const override;
	void Update(Uint64 delta) override;

	void OnCollisionEnter(CollisionResult) override;
};

