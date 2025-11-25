#pragma once
#include "Instrument.h"

class Maracas : public Instrument
{
public:
	Maracas(char id) : Instrument(id) {
		name = "Maracas";
		size = vector2(LEVEL_TILE_SIZE / 2.5);
		AddCollider(size, ECollisionLayer::LObject)->SetCollisionType(ECollisionType::MOVABLE);
	}

	void Init() override;

	void Play() override;
};

