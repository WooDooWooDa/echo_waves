#pragma once
#include "LitableGameObject.h"
#include "IInteractable.h"

class Key : public LitableGameObject, public IInteractable
{
private:
	char keyId;
	bool isHover = false;

	CollisionComponent* collectCollider;

public:
	Key(char id) : LitableGameObject() {
		name = "Key";
		keyId = id;
		size = LEVEL_TILE_SIZE / 4;
		AddCollider(size, ECollisionLayer::LObject);
		collectCollider = AddCollider(vector2(LEVEL_TILE_SIZE / 2), ECollisionLayer::LInteraction);
		collectCollider->isTrigger = true;
	}

	void Init() override;
	void Draw(SDL_Renderer*) const override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;
};

