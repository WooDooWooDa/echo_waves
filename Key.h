#pragma once
#include "GameObject.h"
#include "IInteractable.h"

class Key : public GameObject, public IInteractable
{
private:
	char keyId;

	CollisionComponent* collectCollider;

public:
	Key(char id) : GameObject() {
		name = "Key";
		keyId = id;
		size = LEVEL_TILE_SIZE / 4;
		AddCollider(size)->SetLayer(ECollisionLayer::LWall);
		collectCollider = AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction);
		collectCollider->isTrigger = true;
	}

	void OnTriggerEnter(GameObject* other) override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;
};

