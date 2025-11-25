#pragma once
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include "Player.h"
#include "Level.h"
#include "LevelManager.h"
#include "Text.h"
#include "MenuPanel.h"
#include <string>
#include <unordered_map>

class WaveGame
{
public:
	WaveGame() = default;
	void HandleInputs(SDL_Event* event, SDL_Scancode key_code);
	void InitGame();
	void Update(const Uint64 delta);
	void Draw(SDL_Renderer* renderer) const;

private:
	bool isGameDone = false;
	int currentLevelNumber = 1;
	std::shared_ptr<Player> player;
	std::unique_ptr<LevelManager> levelManager;

	std::unordered_map<std::string, MenuPanel*> panels;

	void RestartLevel();
	void ChangeToLevel(int);
};

