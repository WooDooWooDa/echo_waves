#include "WallTile.h"
#include "SpriteManager.h"
#include <iostream>
#include "SoundParticle.h"

void WallTile::Init()
{
	spriteTexture = SpriteManager::GetTexture(isBroken ? "broken_wall" : "wall");
}

void WallTile::OnTriggerEnter(GameObject* other)
{
	if (!isBroken) return;

	auto particle = dynamic_cast<SoundParticle*>(other);
	if (particle) {
		ResetLitUpTime();
	}
}
