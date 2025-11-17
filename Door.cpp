#include "Door.h"
#include <iostream>
#include "Player.h"
#include "SpriteManager.h"
#include "SoundWave.h"
#include <format>


void Door::Init()
{
	spriteTexture = SpriteManager::GetTexture("close_door");
	openSpriteTexture = SpriteManager::GetTexture("open_door");
}

void Door::Draw(SDL_Renderer* renderer) const
{
	LitableGameObject::Draw(renderer);

	if (isHover && IsLitUp()) {
		std::string text = isLocked ? std::format("Door {} locked", doorId) : "Door open";
		IInteractable::ShowInteractText(renderer, text, GetBounds(), color);
	}
}

void Door::UnHover()
{
	isHover = false;
}

void Door::Hover()
{
	isHover = true;
}

void Door::Interact(GameObject* other)
{
	Player* player = dynamic_cast<Player*>(other);
	auto& playerKeys = player->GetKeys();
	auto found = playerKeys.find(unlockedByKey);
	if (isLocked && found != playerKeys.end()) {
		playerKeys.erase(found);
		Unlock();
	}
}

bool Door::HasCorrectKey()
{
	return false;
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
