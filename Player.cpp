#include "Player.h"

void GameObject::Init() {
	position.X = 768.0 / 2;
	position.Y = 768.0 / 2;
	color = vector3(255, 255, 255);
}

void Player::Update(Uint64 delta)
{
	GameObject::Update(delta);
}

void GameObject::Draw(SDL_Renderer* renderer) const
{
	SDL_SetRenderDrawColor(renderer, color.X, color.Y, color.Z, SDL_ALPHA_OPAQUE);
	SDL_FRect rect;
	rect.x = position.X - size / 2;
	rect.y = position.Y - size / 2;
	rect.w = rect.h = size;
	SDL_RenderFillRect(renderer, &rect);
}
