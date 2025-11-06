#pragma once
#include "GameObject.h"
#include <random>

constexpr double pi = 3.14159265358979323846;

class SoundWave : public GameObject
{
private:
	std::random_device random;
	std::uniform_int_distribution<int> waveAngleDist;

	float particleTtl;
	int nbParticles;

	void SpawnParticles();

public:
	SoundWave(int nbSoundParticle, float ttl = 100.0) : GameObject() {
		size = LEVEL_TILE_SIZE / 4;
		nbParticles = nbSoundParticle;
		particleTtl = ttl;
		collision.isCollidable = false;
		waveAngleDist = std::uniform_int_distribution<int>(0, 90);
	}

	void Init() override;
};

