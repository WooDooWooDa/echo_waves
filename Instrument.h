#pragma once
#include "LitableGameObject.h"
#include "IInteractable.h"
#include <functional>

class Instrument : public LitableGameObject, public IInteractable
{
protected:
	char instrumentId;
	bool isPlayable = true;
	bool isHover = false;

public:
	std::function<void(char)> OnPlayDelegate;

	Instrument(char id) : LitableGameObject() {
		instrumentId = id;
		size = vector2(LEVEL_TILE_SIZE / 1.5);
		AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction)->isTrigger = true;
	}

	void Draw(SDL_Renderer*) const override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;

	virtual void Play();
};

