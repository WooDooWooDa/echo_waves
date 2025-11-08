#include "SoundLine.h"

void SoundLine::Update(Uint64 delta)
{
	currentStrength -= delta;
	if (currentStrength <= 0) {
		Destroy();
	}
}

void SoundLine::Draw(SDL_Renderer* renderer) const
{
	SDL_RenderPoint(renderer, position.X, position.Y);
}
