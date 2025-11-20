#include "Tuba.h"
#include "SpriteManager.h"
#include "SoundParticle.h"
#include "SoundWave.h"
#include "GameObjectHelper.h"

void Tuba::Init()
{
	spriteTexture = SpriteManager::GetTexture("tuba");
}

void Tuba::Draw(SDL_Renderer* renderer) const
{
	LitableGameObject::Draw(renderer);

	if (isHover && IsLitUp()) {
		IInteractable::ShowInteractText(renderer, "Play", GetBounds(), color);
	}
}

void Tuba::UnHover()
{
	isHover = false;
}

void Tuba::Hover()
{
	isHover = true;
}

void Tuba::Interact(GameObject*)
{
	Play();
}

void Tuba::Play()
{
	float angleInc = 2.0f * M_PI / 72;
	auto angle = std::atan2(spriteDirection.Y, spriteDirection.X);
	for (size_t i = 0; i < 3; i++)
	{
		auto dir = vector2(cosf(angle), sinf(angle));
		auto p = Instantiate<SoundParticle>(100, position, dir, 7.5);
		p->emitter = this;
		
		if (i != 0) {
			if (std::abs(dir.X) > std::abs(dir.Y)) {
				dir.Y = -dir.Y;
			} else {
				dir.X = -dir.X;
			}

			auto p = Instantiate<SoundParticle>(100, position, dir, 7.5);
			p->emitter = this;
		}
		angle += angleInc;
	}

	ResetLitUpTime();
}
