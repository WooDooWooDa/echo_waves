#pragma once
#include "LitableGameObject.h"
#include "IInteractable.h"
#include "Level.h"

class LevelExit : public LitableGameObject, public IInteractable
{
private:
	bool isHover = false;
	Level* currentLevel;

public:
	LevelExit(Level* level) {
		currentLevel = level;
		size = vector2(LEVEL_TILE_SIZE / 1.2);
		AddCollider(size, ECollisionLayer::LWall);
		AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction)->isTrigger = true;
	}

	void Init() override;
	void Draw(SDL_Renderer*) const override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;
};

