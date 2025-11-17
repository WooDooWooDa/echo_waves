#include "Xylophone.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "SoundWave.h"
#include <format>

void Xylophone::Init()
{
	spriteTexture = SpriteManager::GetTexture("xylophone");
}

void Xylophone::Draw(SDL_Renderer* renderer) const
{
	LitableGameObject::Draw(renderer);

	if (isHover && IsLitUp()) {
		IInteractable::ShowInteractText(renderer, "Play", GetBounds(), color);
	}
}

void Xylophone::UnHover()
{
	isHover = false;
}

void Xylophone::Hover()
{
	isHover = true;
}

void Xylophone::Interact(GameObject* other)
{
	Play();
}

void Xylophone::Play()
{
	SoundManager::PlaySound(std::format("xylophone_{}", std::to_string(soundNumber)), 0.5);

	auto playWave = SoundWave(10, 25);
	playWave.emitter = this;
	playWave.MoveTo(position);
	playWave.Init();

	if (OnPlayDelegate) OnPlayDelegate(xyloId);
	ResetLitUpTime();
}
