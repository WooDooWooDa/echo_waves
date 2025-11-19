#pragma once
#include "LitableGameObject.h"

class WallTile : public LitableGameObject
{
private:
	bool isBroken;
public:
	WallTile(bool broken) : LitableGameObject() {
		name = "Wall";
		isBroken = broken;
		size = LEVEL_TILE_SIZE;

		AddCollider(size)->SetLayer(broken ? ECollisionLayer::LBrokenWall : ECollisionLayer::LWall);
		if (broken)
			AddCollider(size, ECollisionLayer::LBrokenWall)->isTrigger = true;
	}

	void Init() override;

	void OnTriggerEnter(GameObject*) override;
};

