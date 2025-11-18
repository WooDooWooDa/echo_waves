#include "Piano.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "SoundWave.h"
#include <format>

void Piano::Init()
{
	pianoTextures[0] = SpriteManager::GetTexture("piano_0");
	pianoTextures[1] = SpriteManager::GetTexture("piano_1");
	pianoTextures[2] = SpriteManager::GetTexture("piano_2");
	pianoTextures[3] = SpriteManager::GetTexture("piano_3");
	pianoTextures[4] = SpriteManager::GetTexture("piano_4");
	spriteTexture = pianoTextures[currentNote];
}

void Piano::Draw(SDL_Renderer* renderer) const
{
	LitableGameObject::Draw(renderer);

	if (isHover && IsLitUp()) {
		IInteractable::ShowInteractText(renderer, "Play", GetBounds(), color);
	}
}

void Piano::UnHover()
{
	isHover = false;
}

void Piano::Hover()
{
	isHover = true;
}

void Piano::Interact(GameObject*)
{
	ChangeNote();
	Play();
}

void Piano::ChangeNote()
{
	currentNote = (currentNote + 1) % NB_PIANO_NOTES;
	spriteTexture = pianoTextures[currentNote];
}

void Piano::Play()
{
	SoundManager::PlaySound(std::format("piano_{}", std::to_string(currentNote)), 0.5);

	auto playWave = SoundWave(10, 25);
	playWave.emitter = this;
	playWave.MoveTo(position);
	playWave.Init();

	if (OnPlayDelegate) OnPlayDelegate();
	ResetLitUpTime();
}
