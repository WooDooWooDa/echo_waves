#pragma once
#include "Instrument.h"
#include "IInteractable.h"
#include <functional>

class Xylophone : public Instrument
{
private:
	int soundNumber;

public:

	Xylophone(char id, int soundNb) : Instrument(id) {
		name = "Xylophone";
		soundNumber = soundNb;
		size = vector2(LEVEL_TILE_SIZE / 1.5);

		litUpTime = 200;

		AddCollider(size, ECollisionLayer::LWall);
	}
	
	char GetId() const { return instrumentId; }

	void Init() override;

	void Play() override;
};

