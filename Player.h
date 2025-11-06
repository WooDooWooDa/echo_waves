#pragma once
#include "GameObject.h"
#include <random>

class Player : public GameObject
{
private:

	float soundWaveTimer = 100.0;		//~1 sec?
	float currentSoundWaveTimer = 0.0;

	float distanceBetweenStep = LEVEL_TILE_SIZE;
	float distanceMoved = 0.0;
	bool isWalking = false;

public:
	Player() {
		collision.SetLayer(ECollisionLayer::LPlayer);
	}

	void Init() override;
	void Update(Uint64 delta) override;

	void TryLaunchSoundWave(int nbSoundP, float soundPointTTL);

	void OnCollisionEnter(CollisionResult) override;

private:
	void LaunchSoundWave(int nbSoundP, float soundPointTTL);
	void StepSound();
};

