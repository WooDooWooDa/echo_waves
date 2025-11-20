#include "LevelExit.h"
#include "SpriteManager.h"
#include "SoundWave.h"

void LevelExit::Init()
{
	spriteTexture = SpriteManager::GetTexture("stairs");
}

void LevelExit::Draw(SDL_Renderer* renderer) const
{
	LitableGameObject::Draw(renderer);

	if (isHover && IsLitUp() && !currentLevel->IsLevelDone()) {
		IInteractable::ShowInteractText(renderer, "Next level!", GetBounds(), color);
	}
}

void LevelExit::UnHover()
{
	isHover = false;
}

void LevelExit::Hover()
{
	isHover = true;
}

void LevelExit::Interact(GameObject* other)
{	
	if (currentLevel->IsLevelDone()) return;

	auto done = SoundWave(36, 25);
	done.emitter = this;
	done.MoveTo(position);
	done.Init();

	currentLevel->FinishLevel();
}