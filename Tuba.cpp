#include "Tuba.h"
#include "SpriteManager.h"
#include "SoundParticle.h"
#include "SoundWave.h"
#include "GameObjectHelper.h"
#include <numbers>

void Tuba::Init()
{
	spriteTexture = SpriteManager::GetTexture("tuba");
}

void Tuba::OnCollisionEnter(CollisionResult res)
{
	LitableGameObject::OnCollisionEnter(res);

	auto particle = dynamic_cast<SoundParticle*>(res.other);
	if (!particle) return;

	// Particle from instrument?
	auto instrumentParticle = dynamic_cast<Instrument*>(particle->emitter);
	if (instrumentParticle)
		Play();
}

void Tuba::Play()
{
	Instrument::Play();

	float angleInc = 2.0f * std::numbers::pi / 72;
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
}
