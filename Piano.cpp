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

void Piano::ChangeNote()
{
	currentNote = (currentNote + 1) % NB_PIANO_NOTES;
	spriteTexture = pianoTextures[currentNote];
}

void Piano::Play()
{
	ChangeNote();

	Instrument::Play();

	if (currentNote != 0) {
		SoundManager::PlaySound(std::format("piano_{}", 
			std::to_string(currentNote)), 0.3 + (0.1 * currentNote));

		auto playWave = SoundWave(this, 5, 10);
		playWave.MoveTo(position);
		playWave.Init();
	}
}
