#include "Key.h"
#include "Player.h"
#include "SpriteManager.h"
#include "SoundWave.h"

void Key::Init()
{
	spriteTexture = SpriteManager::GetTexture("key");
}

void Key::UnHover()
{

}

void Key::Hover()
{

}

void Key::Interact(GameObject* other)
{
	Player* player = dynamic_cast<Player*>(other);
	player->AddKey(keyId);

	auto pickupWave = SoundWave(5, 10, 2);
	pickupWave.MoveTo(position);
	pickupWave.Init();

	Destroy();
}
