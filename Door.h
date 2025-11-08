#pragma once
#include "GameObject.h"
#include "IInteractable.h"

class Door : public GameObject, public IInteractable
{
private:
	char doorId;
	char unlockedByKey;
	bool isLocked = true;

	CollisionComponent* unlockCollider;

public:
	Door(char id, bool isHorizontal, char key) : GameObject() {
		name = "Door";
		doorId = id;
		unlockedByKey = key;
		size = isHorizontal ? 
			vector2(LEVEL_TILE_SIZE, LEVEL_TILE_SIZE / 4) : 
			vector2(LEVEL_TILE_SIZE / 4, LEVEL_TILE_SIZE);
		AddCollider(size)->SetLayer(ECollisionLayer::LWall);
		unlockCollider = AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction);
		unlockCollider->isTrigger = true;
	}

	void OnTriggerEnter(GameObject* other) override;
	void OnTriggerExit(GameObject* other) override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;

	void Unlock();
};

