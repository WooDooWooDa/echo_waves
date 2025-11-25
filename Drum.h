#pragma once
#include "Instrument.h"

class Drum : public Instrument
{
private:
	bool doorOpened = false;
	char unlockedDoor;

public:
	Drum(char id, char doorId) : Instrument(id) {
		name = "Drum";
		unlockedDoor = doorId;
		size = vector2(LEVEL_TILE_SIZE / 2);
		AddCollider(size, ECollisionLayer::LObject)->SetCollisionType(ECollisionType::MOVABLE);
	}

	void Init() override;

	void OnCollisionEnter(CollisionResult) override;

	void Play() override;
};

