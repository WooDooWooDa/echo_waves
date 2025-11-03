#pragma once
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_render.h>
#include "Player.h"
#include <memory>

class WaveGame
{
public:
	void HandleInputs(SDL_Event* event, SDL_Scancode key_code);
	void InitGame();
	void Update(const Uint64 delta);
	void Draw(SDL_Renderer* renderer) const;

private:
	~WaveGame();
	Player* player;
};

