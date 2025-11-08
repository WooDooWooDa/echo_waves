#pragma once
#include "GameObject.h"
#include <random>

class Player : public GameObject
{
private:
	float soundWaveTimer = 100.0;		//~1 sec?
	float currentSoundWaveTimer = 0.0;

	float distanceBetweenStep = LEVEL_TILE_SIZE / 2;
	float distanceMoved = 0.0;
	bool isWalking = false;

public:
	Player() {
		name = "Player";
		speed = 2.0;
		size = LEVEL_TILE_SIZE / 4;
		AddCollider(size)->SetLayer(ECollisionLayer::LPlayer);
	}

	void Init() override;
	void Update(Uint64 delta) override;

	void TryLaunchSoundWave(int nbSoundP, float soundPointTTL);

	void OnCollisionEnter(CollisionResult) override;

	void TryInteract();

private:
	void LaunchSoundWave(int nbSoundP, float soundPointTTL, float spd);
	void StepSound();
};

