#include "Maracas.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "GameObjectHelper.h"
#include "SoundParticle.h"

void Maracas::Init()
{
	spriteTexture = SpriteManager::GetTexture("maracas");
}

void Maracas::Play()
{
	Instrument::Play();

	SoundManager::PlaySound("maracas", 0.15);

	auto inc = std::numbers::pi / 2;
	auto angle = 0.0;
	for (size_t i = 0; i < 4; i++)
	{
		auto dir = vector2(cosf(angle), sinf(angle));
		auto p = Instantiate<SoundParticle>(200, position, dir, 7.5);
		p->emitter = this;
		angle += inc;
	}
}
