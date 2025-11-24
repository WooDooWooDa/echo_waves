#pragma once
#include "Instrument.h"
#include "IInteractable.h"

class Tuba : public Instrument
{
public:
	Tuba(char id) : Instrument(id) {
		name = "Tuba";
		AddCollider(size, ECollisionLayer::LObject)->SetCollisionType(ECollisionType::MOVABLE);
	}

	void Init() override;

	void OnCollisionEnter(CollisionResult) override;

	void Play() override;
};

