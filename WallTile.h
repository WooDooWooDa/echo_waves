#pragma once
#include "GameObject.h"

class WallTile : public GameObject
{
public:
	WallTile() {
		size = LEVEL_TILE_SIZE;
		collision.SetLayer(ECollisionLayer::LWall);
	}
};

