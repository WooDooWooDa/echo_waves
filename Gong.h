#pragma once
#include "LitableGameObject.h"
#include "Door.h"

class Gong : public LitableGameObject
{
private:
	char unlockedDoor;
	bool banged = false;

	Door* doorLinked = nullptr;

public:
	Gong(char id, char unlockedDoor) : LitableGameObject() {
		name = "Gong";
		this->unlockedDoor = unlockedDoor;
		size = vector2(LEVEL_TILE_SIZE / 1.2);
		litUpTime = 100.0;
		AddCollider(size, ECollisionLayer::LWall);
	}

	void Init() override;
	void Update(Uint64) override;

	void OnCollisionEnter(CollisionResult) override;

	void Bang();
};

