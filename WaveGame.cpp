#include "WaveGame.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include "gameSettings.h"

void WaveGame::InitGame()
{
	levelManager = make_unique<LevelManager>();

	player = make_shared<Player>();
	player->Init();

	startText = make_unique<Text>();
	startText->SetText("Press SPACE to clap", 72);

	if (levelManager->LoadAllLevels()) {
		//Load to first level
		currentLevelNumber = 2;
		ChangeToLevel(currentLevelNumber);
	}
	
	// Load itch cover img level
	//auto level = levelManager->LoadSpecialLevel("itch_title_level");
	//levelManager->AddGameObjectToLevel(player);
	//player->MoveTo(level->GetPlayerSpawn());
}

void WaveGame::Update(const Uint64 delta)
{
	if (isGameDone) return;

	if (levelManager->GetCurrentLevel() == nullptr) return;

	levelManager->GetCurrentLevel()->Update(delta);

	if (levelManager->GetCurrentLevel()->IsLevelDone()) {
		if (currentLevelNumber > levelManager->GetNbLevels()) {
			isGameDone = true;
			// Show win/thanks screen!
		}
		currentLevelNumber++;
		ChangeToLevel(currentLevelNumber);
	}
}

void WaveGame::Draw(SDL_Renderer* renderer) const
{
	if (isGameDone) return;

	if (levelManager->GetCurrentLevel())
		levelManager->GetCurrentLevel()->Draw(renderer);
	
	//todo : Replace by menu panel
	if (!removedStartText)
		startText->Draw(renderer, vector2(GAME_WINDOW_SIZE / 2));
}

void WaveGame::RestartLevel() {
	ChangeToLevel(currentLevelNumber);
}

void WaveGame::ChangeToLevel(int level)
{
	// Remove player from previous/current level if any
	player->Restart();
	levelManager->RemoveGameObjectFromLevel(player);
	levelManager->SetCurrentLevel(level);
	// Add player to new level
	levelManager->AddGameObjectToLevel(player);
	player->MoveTo(levelManager->GetCurrentLevel()->GetPlayerSpawn());

	removedStartText = false;
}

void WaveGame::HandleInputs(SDL_Event* event, SDL_Scancode key_code)
{
	if (!removedStartText) {
		if (event->type == SDL_EVENT_KEY_DOWN) {
			switch (key_code)
			{
			case SDL_SCANCODE_SPACE:
				player->TryLaunchSoundWave(36, 100);
				RemoveStartText();
			default:
				break;
			}
		}
		return;
	}

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
		case SDL_SCANCODE_R:
			player->Restart();
			RestartLevel();
			break;
		case SDL_SCANCODE_V:
			SETTINGS::SHOW_COLLIDER_MODE = (SETTINGS::SHOW_COLLIDER_MODE + 1) % 2;
			break;
		case SDL_SCANCODE_C:
			SETTINGS::SHOW_COLLIDERS = !SETTINGS::SHOW_COLLIDERS;
			break;
		case SDL_SCANCODE_L:
			levelManager->GetCurrentLevel()->FinishLevel();
			break;
		default:
			break;
		}
	}
}

void WaveGame::RemoveStartText()
{
	if (startText) {
		//startText.reset(nullptr);
		removedStartText = true;
	}
}
