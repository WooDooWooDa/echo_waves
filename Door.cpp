#include "Door.h"
#include <iostream>
#include "Player.h"
#include "SpriteManager.h"
#include "SoundWave.h"

void Door::Init()
{
	spriteTexture = SpriteManager::GetTexture("close_door");
	openSpriteTexture = SpriteManager::GetTexture("open_door");
}

void Door::UnHover()
{
}

void Door::Hover()
{
}

void Door::Interact(GameObject* other)
{
	Player* player = dynamic_cast<Player*>(other);
	auto& playerKeys = player->GetKeys();
	auto found = playerKeys.find(unlockedByKey);
	if (isLocked && found != playerKeys.end()) {
		player->GetKeys().erase(found);
		Unlock();
	}
}

void Door::Unlock()
{
	auto pickupWave = SoundWave(20, 50);
	pickupWave.MoveTo(position);
	pickupWave.Init();

	isLocked = false;
	spriteTexture = openSpriteTexture;
	colliders.at(0)->isCollidable = false;
	ResetLitUpTime();
}
