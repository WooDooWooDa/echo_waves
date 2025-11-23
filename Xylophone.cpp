#include "Xylophone.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "SoundWave.h"
#include <format>

void Xylophone::Init()
{
	spriteTexture = SpriteManager::GetTexture("xylophone");
}

void Xylophone::Play()
{
	Instrument::Play();

	SoundManager::PlaySound(std::format("xylophone_{}", std::to_string(soundNumber)), 0.5);

	auto playWave = SoundWave(this, 10, 25);
	playWave.MoveTo(position);
	playWave.Init();
}
