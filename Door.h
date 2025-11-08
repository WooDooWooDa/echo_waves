#pragma once
#include "GameObject.h"

class Door : public GameObject
{
private:
	char doorId;
	bool isLocked = true;

	CollisionComponent* unlockCollider;

public:
	Door(char id, bool isHorizontal) : GameObject() {
		doorId = id;
		size = isHorizontal ? 
			vector2(LEVEL_TILE_SIZE, LEVEL_TILE_SIZE / 4) : 
			vector2(LEVEL_TILE_SIZE / 4, LEVEL_TILE_SIZE);
		AddCollider(size)->SetLayer(ECollisionLayer::LWall);
		unlockCollider = AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction);
		unlockCollider->isTrigger = true;
	}

	void OnTriggerEnter(GameObject* other) override;

	void Unlock();
};

