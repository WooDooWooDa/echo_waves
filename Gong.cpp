#include "Gong.h"
#include "SpriteManager.h"
#include "SoundParticle.h"
#include <format>
#include "SoundManager.h"
#include "SoundWave.h"
#include "LevelManager.h"

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
		doorLinked->Lock();
	}
}

void Gong::OnCollisionEnter(CollisionResult res)
{
	if (banged) return;

	auto particle = dynamic_cast<SoundParticle*>(res.other);
	if (particle) {
		Bang();
	}
}

void Gong::Bang()
{
	banged = true;
	//SoundManager::PlaySound(std::format("gong"));

	auto gongWave = SoundWave(20, 25);
	gongWave.emitter = this;
	gongWave.MoveTo(position);
	gongWave.Init();

	if (doorLinked->isLocked) {
		doorLinked->Unlock();
	}

	ResetLitUpTime();
}
