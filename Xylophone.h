#pragma once
#include "LitableGameObject.h"
#include "IInteractable.h"
#include <functional>

class Xylophone : public LitableGameObject, public IInteractable
{
private:
	char xyloId;
	bool isHover = false;

public:
	std::function<void(char)> OnPlayDelegate;

	Xylophone(char id) : LitableGameObject() {
		name = "Xylophone";
		xyloId = id;
		size = vector2(LEVEL_TILE_SIZE / 2);

		litUpTime = 200;

		AddCollider(size, ECollisionLayer::LWall);
		AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction)->isTrigger = true;
	}
	
	char GetId() const { return xyloId; }

	void Init() override;
	void Draw(SDL_Renderer*) const override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;

	void Play();
};

