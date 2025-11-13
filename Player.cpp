#include "Player.h"
#include <iostream>
#include "SoundWave.h"
#include "LevelManager.h"
#include "LitableGameObject.h"
#include "SpriteManager.h"
#include "SoundManager.h"

void Player::Init()
{
	spriteTexture = SpriteManager::GetTexture("clap");
	litUpTime = 20.0;
}

void Player::Update(Uint64 delta)
{
	auto lastPos = position;
	LitableGameObject::Update(delta);

	if (currentSoundWaveTimer >= 0)
		currentSoundWaveTimer -= delta;

	auto posDiff = lastPos - position;
	isWalking = posDiff.Length() > 0;
	if (isWalking) {
		distanceMoved += posDiff.Length();

		if (distanceMoved >= distanceBetweenStep) {
			StepSound();
			distanceMoved = 0;
		}
	}
}

void Player::TryLaunchSoundWave(int nbSoundPoint, float soundPointTTL)
{
	if (currentSoundWaveTimer >= 0) return;

	LaunchSoundWave(nbSoundPoint, soundPointTTL, 5.0);
	ResetLitUpTime();
	SoundManager::PlaySound("clap", 0.1);

	currentSoundWaveTimer = soundWaveTimer;
}

void Player::OnTriggerEnter(GameObject* other)
{
	if (other == nullptr) return;

	IInteractable* interactable = dynamic_cast<IInteractable*>(other);
	if (interactable != nullptr) {
		currentInteractable = interactable;
		currentInteractable->Hover();
	}
}

void Player::OnTriggerExit(GameObject* other)
{
	if (other == nullptr) return;

	IInteractable* interactable = dynamic_cast<IInteractable*>(other);
	if (interactable != nullptr && interactable == currentInteractable) {
		currentInteractable->UnHover();
		currentInteractable = nullptr;
	}
}

void Player::OnCollisionEnter(CollisionResult res) { }

void Player::TryInteract()
{
	if (currentInteractable != nullptr) {
		LitableGameObject* litable = dynamic_cast<LitableGameObject*>(currentInteractable);
		if (litable && !litable->IsLitUp()) return;

		currentInteractable->Interact(this);
	}
}

void Player::LaunchSoundWave(int nbSoundP, float soundPointTTL, float speed)
{
	auto wave = SoundWave(nbSoundP, soundPointTTL, speed);
	wave.MoveTo(position);
	wave.Init();
}

void Player::StepSound()
{
	LaunchSoundWave(5, 10, 1.0);
	std::random_device rd;
	std::mt19937 gen(rd());
	int step = nb_steps(gen);
	SoundManager::PlaySound("step_" + std::to_string(step), step_volume(gen));
}
