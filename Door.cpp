#include "Door.h"
#include <iostream>
#include "Player.h"

void Door::OnTriggerEnter(GameObject* other) { }

void Door::OnTriggerExit(GameObject* other) { }

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
	isLocked = false;
	Destroy();
}
