#pragma once
#include "LitableGameObject.h"
#include <random>
#include "IInteractable.h"
#include <set>

class Player : public LitableGameObject
{
private:
	float soundWaveTimer = 100.0;		//~1 sec?
	float currentSoundWaveTimer = 0.0;

	float distanceBetweenStep = LEVEL_TILE_SIZE / 2;
	float distanceMoved = 0.0;
	bool isWalking = false;
	std::uniform_int_distribution<> nb_steps = std::uniform_int_distribution<>(1, 3);
	std::uniform_real_distribution<> step_volume = std::uniform_real_distribution<>(0.1, 0.25);

	IInteractable* currentInteractable = nullptr;

	std::set<char> keys;

public:
	Player() {
		name = "Player";
		speed = 2.0;
		size = LEVEL_TILE_SIZE / 4;
		AddCollider(size, ECollisionLayer::LPlayer);
	}

	void Init() override;
	void Update(Uint64 delta) override;

	void TryLaunchSoundWave(int nbSoundP, float soundPointTTL);

	void OnTriggerEnter(GameObject*) override;
	void OnTriggerExit(GameObject*) override;
	void OnCollisionEnter(CollisionResult) override;

	void TryInteract();
	void AddKey(char key) { keys.insert(key); }
	std::set<char>& GetKeys() { return keys; }

private:
	void LaunchSoundWave(int nbSoundP, float soundPointTTL, float spd);
	void StepSound();
};

