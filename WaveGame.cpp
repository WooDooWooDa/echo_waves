#include "WaveGame.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include "LevelFileReader.h"

void WaveGame::InitGame()
{
	player = std::make_shared<Player>();
	player->Init();
	if (levelManager.LoadAllLevels()) {
		currentLevel = levelManager.GetLevel(1);
		currentLevel->AddGameObject(player);
		player->MoveTo(currentLevel->GetPlayerSpawn());
	}
}

void WaveGame::Update(const Uint64 delta)
{
	player->Update(delta);

	if (currentLevel != nullptr)
		currentLevel->Update(delta);

	collisionSystem.CheckCollision(currentLevel);
}

void WaveGame::Draw(SDL_Renderer* renderer) const
{
	player->Draw(renderer);

	if (currentLevel != nullptr)
		currentLevel->Draw(renderer);
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
		default:
			break;
		}
	}
}
