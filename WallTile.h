#pragma once
#include "GameObject.h"

class WallTile : public GameObject
{
public:
	WallTile() {
		size = LEVEL_TILE_SIZE;
		AddCollider(size)->SetLayer(ECollisionLayer::LWall);
	}
};

