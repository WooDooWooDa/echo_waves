#include "Instrument.h"

void Instrument::Draw(SDL_Renderer* renderer) const
{
	LitableGameObject::Draw(renderer);

	if (isPlayable && isHover && IsLitUp()) {
		IInteractable::ShowInteractText(renderer, "Play", GetBounds(), color);
	}
}

void Instrument::UnHover()
{
	isHover = false;
}

void Instrument::Hover()
{
	isHover = true;
}

void Instrument::Interact(GameObject*)
{
	if (isPlayable)
		Play();
}

void Instrument::Play()
{
	if (OnPlayDelegate) OnPlayDelegate(instrumentId);

	ResetLitUpTime();
}
