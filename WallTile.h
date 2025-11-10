#pragma once
#include "LitableGameObject.h"

class WallTile : public LitableGameObject
{
public:
	WallTile() : LitableGameObject() {
		size = LEVEL_TILE_SIZE;
		AddCollider(size, ECollisionLayer::LWall);
	}

	void Init() override;
};

