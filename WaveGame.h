#pragma once
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include "Player.h"
#include "Level.h"
#include "LevelManager.h"
#include "CollisionSystem.h"

class WaveGame
{
public:
	void HandleInputs(SDL_Event* event, SDL_Scancode key_code);
	void InitGame();
	void Update(const Uint64 delta);
	void Draw(SDL_Renderer* renderer) const;

private:
	std::shared_ptr<Player> player;
	std::unique_ptr<LevelManager> levelManager;
	CollisionSystem collisionSystem;

	void ChangeToLevel(int);
};

