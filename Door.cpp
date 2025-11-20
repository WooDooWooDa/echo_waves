#include "Door.h"
#include <iostream>
#include "Player.h"
#include "SpriteManager.h"
#include "SoundWave.h"
#include <format>
#include "SoundManager.h"


void Door::Init()
{
	closeSpriteTexture = SpriteManager::GetTexture("close_door");
	openSpriteTexture = SpriteManager::GetTexture("open_door");
	spriteTexture = closeSpriteTexture;
}

void Door::Draw(SDL_Renderer* renderer) const
{
	LitableGameObject::Draw(renderer);

	if (isHover && IsLitUp()) {
		std::string text = isLocked ? "Door locked" : "Door open";
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
	SoundManager::PlaySound("open_door", 0.5);

	auto pickupWave = SoundWave(this, 20, 25);
	pickupWave.MoveTo(position);
	pickupWave.Init();

	isLocked = false;
	spriteTexture = openSpriteTexture;
	colliders.at(0)->isCollidable = false;
	ResetLitUpTime();
}

void Door::Lock()
{
	isLocked = true;
	spriteTexture = closeSpriteTexture;
	colliders.at(0)->isCollidable = true;
	ResetLitUpTime();
}
