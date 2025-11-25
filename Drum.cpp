#include "Drum.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "SoundParticle.h"
#include "Door.h"
#include "LevelManager.h"

void Drum::Init()
{
	spriteTexture = SpriteManager::GetTexture("drum");
}

void Drum::OnCollisionEnter(CollisionResult res)
{
	LitableGameObject::OnCollisionEnter(res);

	if (doorOpened) return;

	auto particle = dynamic_cast<SoundParticle*>(res.other);
	if (!particle) return;

	// Particle from instrument?
	auto instrumentParticle = dynamic_cast<Instrument*>(particle->emitter);
	if (instrumentParticle)
		Play();
}

void Drum::Play()
{
	if (doorOpened) return;

	Instrument::Play();

	SoundManager::PlaySound("drum", 1.2);

	auto doors = LevelManager::GetObjectsOfType<Door>();
	for (auto& door : doors) {
		if (door->doorId == unlockedDoor) {
			door->Unlock();
		}
	}

	isPlayable = false;
	doorOpened = true;
}
