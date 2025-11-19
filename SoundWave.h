#pragma once
#include "GameObject.h"
#include <random>
#include <corecrt_math_defines.h>

class SoundWave : public GameObject
{
private:
	std::random_device random;
	std::uniform_int_distribution<int> waveAngleDist;

	float particleTtl;
	int nbParticles;
	float speed;

	void SpawnParticles();

public:
	GameObject* emitter = nullptr;

	SoundWave(int nbSoundParticle, float ttl = 100.0, float spd = 5) {
		size = LEVEL_TILE_SIZE / 4;
		nbParticles = nbSoundParticle;
		particleTtl = ttl;
		speed = spd;
		waveAngleDist = std::uniform_int_distribution<int>(0, M_PI / 2);
	}

	void Init() override;
};

