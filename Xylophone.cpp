#include "Xylophone.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "SoundWave.h"

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
	ResetLitUpTime();
}

void Xylophone::Play()
{
	//SoundManager::PlaySound("xylophone_1");

	auto playWave = SoundWave(5, 20, 5);
	playWave.emitter = this;
	playWave.MoveTo(position);
	playWave.Init();

	OnPlayDelegate(xyloId);
}
