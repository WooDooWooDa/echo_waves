#include "Key.h"
#include "Player.h"
#include "SpriteManager.h"
#include "SoundWave.h"
#include "SoundManager.h"
#include <format>

void Key::Init()
{
	spriteTexture = SpriteManager::GetTexture("key");
}

void Key::Draw(SDL_Renderer* renderer) const
{
	LitableGameObject::Draw(renderer);

	if (isHover && IsLitUp()) {
		IInteractable::ShowInteractText(renderer, std::format("Key {}", keyId), GetBounds(), color);
	}
}

void Key::UnHover()
{
	isHover = false;
}

void Key::Hover()
{
	isHover = true;
}

void Key::Interact(GameObject* other)
{
	Player* player = dynamic_cast<Player*>(other);
	player->AddKey(keyId);
	SoundManager::PlaySound("pick_up_key");

	auto pickupWave = SoundWave(this, 5, 10, 2);
	pickupWave.MoveTo(position);
	pickupWave.Init();

	Destroy();
}
