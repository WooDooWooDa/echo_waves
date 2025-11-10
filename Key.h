#pragma once
#include "LitableGameObject.h"
#include "IInteractable.h"

class Key : public LitableGameObject, public IInteractable
{
private:
	char keyId;

	CollisionComponent* collectCollider;

public:
	Key(char id) : LitableGameObject() {
		name = "Key";
		keyId = id;
		size = LEVEL_TILE_SIZE / 4;
		AddCollider(size, ECollisionLayer::LWall);
		collectCollider = AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction);
		collectCollider->isTrigger = true;
	}

	void Init() override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;
};

