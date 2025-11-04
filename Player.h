#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player() {
		collision.SetLayer(ECollisionLayer::LPlayer);
	}

	void Init() override;
	void Update(Uint64 delta) override;
	void OnCollisionEnter(GameObject* other) override;
};

