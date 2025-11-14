#include "SoundWave.h"
#include <iostream>
#include "SoundParticle.h"
#include "LevelManager.h"
#include <numbers>

void SoundWave::Init()
{
	SpawnParticles();
}

void SoundWave::SpawnParticles()
{
	float angleInc = 2.0f * pi / nbParticles;
	float angle = waveAngleDist(random);
	for (size_t i = 0; i < nbParticles; i++)
	{
		auto dir = vector2(cosf(angle), sinf(angle));

		auto newParticle = std::make_shared<SoundParticle>(particleTtl, position, dir, speed);
		newParticle->emitter = emitter;
		LevelManager::AddGameObjectToLevel(newParticle);

		angle += angleInc;
	}
}
