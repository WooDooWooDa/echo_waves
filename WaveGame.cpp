#include "WaveGame.h"
#include "SoundManager.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include "gameSettings.h"
#include "FontManager.h"
#include <format>
#include "WinPanel.h"
#include "StartLevelPanel.h"

void WaveGame::InitGame()
{
	levelManager = make_unique<LevelManager>();

	player = make_shared<Player>();
	player->Init();

	auto startText = new StartLevelPanel();
	startText->Init();
	panels.insert({ "start", startText });

	auto winPanel = new WinPanel();
	winPanel->Init();
	panels.insert({ "win", winPanel });

	if (levelManager->LoadAllLevels()) {
		//Load to first level
		ChangeToLevel(currentLevelNumber);
	}
}

void WaveGame::Update(const Uint64 delta)
{
	if (levelManager->GetCurrentLevel() == nullptr) return;

	levelManager->GetCurrentLevel()->Update(delta);

	// Win check
	if (!isGameDone && levelManager->GetCurrentLevel()->IsLevelDone()) {
		if (currentLevelNumber > levelManager->GetNbLevels()) {
			isGameDone = true;
			panels["start"]->Hide();
			panels["win"]->Show();
			return;
		}
		currentLevelNumber++;
		ChangeToLevel(currentLevelNumber);
	}
}

void WaveGame::Draw(SDL_Renderer* renderer) const
{
	for (auto& panel : panels) {
		panel.second->Draw(renderer);
	}

	if (isGameDone) return;

	if (levelManager->GetCurrentLevel())
		levelManager->GetCurrentLevel()->Draw(renderer);
}

void WaveGame::RestartLevel() {
	ChangeToLevel(currentLevelNumber);
	SoundManager::StopAll();
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

	auto panel = ((StartLevelPanel*)panels["start"]);
	panel->SetLevelNumber(currentLevelNumber);
	panel->Show();
}

void WaveGame::HandleInputs(SDL_Event* event, SDL_Scancode key_code)
{
	if (isGameDone) return;

	if (panels["start"]->GetVisibility()) {
		if (event->type == SDL_EVENT_KEY_DOWN) {
			switch (key_code)
			{
			case SDL_SCANCODE_SPACE:
				player->TryLaunchSoundWave(36, 100);
				panels["start"]->Hide();
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
