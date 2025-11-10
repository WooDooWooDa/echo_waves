#include "WallTile.h"
#include "SpriteManager.h"

void WallTile::Init()
{
	spriteTexture = SpriteManager::GetTexture("wall");
}
