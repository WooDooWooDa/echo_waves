#pragma once
#include "LitableGameObject.h"
#include "IInteractable.h"

class Door : public LitableGameObject, public IInteractable
{
private:
	char unlockedByKey;
	bool isLocked = true;
	bool isHover = false;

	SDL_Texture* openSpriteTexture;

	CollisionComponent* unlockCollider;

public:
	char doorId;

	Door(char id, bool isHorizontal, char key) : LitableGameObject() {
		name = "Door";
		doorId = id;
		unlockedByKey = key;
		size = vector2(LEVEL_TILE_SIZE);
		auto colliderSize = isHorizontal ? 
			vector2(LEVEL_TILE_SIZE, LEVEL_TILE_SIZE / 2) : 
			vector2(LEVEL_TILE_SIZE / 2, LEVEL_TILE_SIZE);
		AddCollider(colliderSize, ECollisionLayer::LWall);
		unlockCollider = AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction);
		unlockCollider->isTrigger = true;
	}

	void Init() override;
	void Draw(SDL_Renderer*) const override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;

	bool HasCorrectKey();
	void Unlock();
};

