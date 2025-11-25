#include "Gong.h"
#include "SpriteManager.h"
#include "SoundParticle.h"
#include <format>
#include "SoundManager.h"
#include "SoundWave.h"
#include "LevelManager.h"
#include "Instrument.h"

void Gong::Init()
{
	spriteTexture = SpriteManager::GetTexture("gong");

	auto doors = LevelManager::GetObjectsOfType<Door>();
	for (auto& door : doors) {
		if (door->doorId == unlockedDoor) {
			doorLinked = door;
		}
	}
}

void Gong::Update(Uint64 delta)
{
	LitableGameObject::Update(delta);

	if (banged && litUpTimeLeft <= 0) {
		banged = false;
		if (doorLinked)
			doorLinked->Lock();
	}
}

void Gong::OnCollisionEnter(CollisionResult res)
{
	if (banged) return;

	auto particle = dynamic_cast<SoundParticle*>(res.other);
	if (!particle) return;

	// Particle from instrument?
	auto instrumentParticle = dynamic_cast<Instrument*>(particle->emitter);
	if (instrumentParticle)
		Bang();
}

void Gong::Bang()
{
	banged = true;
	SoundManager::PlaySound("gong", 0.25);

	auto gongWave = SoundWave(this, 20, 50);
	gongWave.MoveTo(position);
	gongWave.Init();

	if (doorLinked && doorLinked->isLocked) {
		doorLinked->Unlock();
	}

	ResetLitUpTime();
}
