#include "Player.h"
#include <iostream>
#include "SoundWave.h"
#include "LevelManager.h"

void Player::Init()
{
	
}

void Player::Update(Uint64 delta)
{
	auto lastPos = position;
	GameObject::Update(delta);

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

	currentSoundWaveTimer = soundWaveTimer;
}

void Player::OnCollisionEnter(CollisionResult res)
{
	
}

void Player::TryInteract()
{

}

void Player::LaunchSoundWave(int nbSoundP, float soundPointTTL, float speed)
{
	auto wave = SoundWave(nbSoundP, soundPointTTL, speed);
	wave.MoveTo(position);
	wave.Init();
}

void Player::StepSound()
{
	LaunchSoundWave(5, 10, 2.0);
}
