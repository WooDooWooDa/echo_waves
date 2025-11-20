#pragma once
#include "LitableGameObject.h"
#include "IInteractable.h"

class Tuba : public LitableGameObject, public IInteractable
{
private:
	bool isHover = false;
	vector2 soundDirection;

public:
	char tubaId;
	Tuba(char id) {
		tubaId = id;

		size = vector2(LEVEL_TILE_SIZE / 1.5);

		AddCollider(size, ECollisionLayer::LObject)->SetCollisionType(ECollisionType::MOVABLE);
		AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction)->isTrigger = true;
	}

	void Init() override;
	void Draw(SDL_Renderer*) const override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;

	void Play();
};

