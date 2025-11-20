#include "WaveGame.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include "gameSettings.h"

void WaveGame::InitGame()
{
	levelManager = make_unique<LevelManager>();

	player = make_shared<Player>();
	player->Init();

	if (levelManager->LoadAllLevels()) {
		//Load to first level
		ChangeToLevel(1);
	}
}

void WaveGame::Update(const Uint64 delta)
{
	if (levelManager->GetCurrentLevel())
		levelManager->GetCurrentLevel()->Update(delta);
}

void WaveGame::Draw(SDL_Renderer* renderer) const
{
	if (levelManager->GetCurrentLevel())
		levelManager->GetCurrentLevel()->Draw(renderer);
}

void WaveGame::ChangeToLevel(int)
{
	// Remove player from previous/current level if any
	levelManager->RemoveGameObjectFromLevel(player);
	levelManager->SetCurrentLevel(1);
	// Add player to new level
	levelManager->AddGameObjectToLevel(player);
	player->MoveTo(levelManager->GetCurrentLevel()->GetPlayerSpawn());
}

void WaveGame::HandleInputs(SDL_Event* event, SDL_Scancode key_code)
{
	if (event->type == SDL_EVENT_KEY_UP) {
		switch (key_code)
		{
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			player->SetVelocityX(0);
			break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			player->SetVelocityX(0);
			break;
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			player->SetVelocityY(0);
			break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			player->SetVelocityY(0);
			break;
		default:
			break;
		}
	}
	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (key_code)
		{
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			player->SetVelocityX(-1);
			break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			player->SetVelocityX(1);
			break;
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			player->SetVelocityY(-1);
			break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			player->SetVelocityY(1);
			break;
		case SDL_SCANCODE_SPACE:
			player->TryLaunchSoundWave(36, 100);
			break;
		case SDL_SCANCODE_E:
			player->TryInteract();
			break;
		case SDL_SCANCODE_V:
			SETTINGS::SHOW_COLLIDER_MODE = (SETTINGS::SHOW_COLLIDER_MODE + 1) % 2;
			break;
		case SDL_SCANCODE_C:
			SETTINGS::SHOW_COLLIDERS = !SETTINGS::SHOW_COLLIDERS;
			break;
		default:
			break;
		}
	}
}
