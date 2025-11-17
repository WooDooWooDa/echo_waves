#pragma once
#include "LitableGameObject.h"
#include "IInteractable.h"
#include <functional>

class Xylophone : public LitableGameObject, public IInteractable
{
private:
	char xyloId;
	int soundNumber;
	bool isHover = false;

public:
	std::function<void(char)> OnPlayDelegate;

	Xylophone(char id, int soundNb) : LitableGameObject() {
		name = "Xylophone";
		xyloId = id;
		soundNumber = soundNb;
		size = vector2(LEVEL_TILE_SIZE / 1.5);

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

