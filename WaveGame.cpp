#include "WaveGame.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>


void WaveGame::InitGame()
{
	player = new Player();
	player->Init();
}

void WaveGame::Update(const Uint64 delta)
{
	player->Update(delta);
}

void WaveGame::Draw(SDL_Renderer* renderer) const
{
	player->Draw(renderer);
}

void WaveGame::HandleInputs(SDL_Event* event, SDL_Scancode key_code)
{
	if (event->type == SDL_EVENT_KEY_UP) {
		switch (key_code)
		{
		case SDL_SCANCODE_A:
			player->SetVelocityX(0);
			break;
		case SDL_SCANCODE_D:
			player->SetVelocityX(0);
			break;
		case SDL_SCANCODE_W:
			player->SetVelocityY(0);
			break;
		case SDL_SCANCODE_S:
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
			player->SetVelocityX(-1);
			break;
		case SDL_SCANCODE_D:
			player->SetVelocityX(1);
			break;
		case SDL_SCANCODE_W:
			player->SetVelocityY(-1);
			break;
		case SDL_SCANCODE_S:
			player->SetVelocityY(1);
			break;
		default:
			break;
		}
	}
}

WaveGame::~WaveGame()
{
	delete player;
}
