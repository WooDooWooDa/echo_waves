#include "LevelExit.h"
#include "SpriteManager.h"
#include "SoundWave.h"
#include "SoundManager.h"
#include "LevelManager.h"
#include "Player.h"

void LevelExit::Init()
{
	spriteTexture = SpriteManager::GetTexture("stairs");
}

void LevelExit::Update(Uint64 delta)
{
	LitableGameObject::Update(delta);

	if (!finishing) return;

	if (finishingTime <= 0) {
		currentLevel->FinishLevel();
	}
	else {
		finishingTime -= delta;
	}
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

	colliders[1]->isCollidable = false;

	auto done = SoundWave(this, 36, 50);
	done.MoveTo(position);
	done.Init();

	auto player = LevelManager::GetObjectsOfType<Player>()[0];
	player->isEnable = false;

	SoundManager::PlaySound("exit", 0.25);
	finishing = true;
}