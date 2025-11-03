#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	void Update(Uint64 delta) override;
	Player() = default;
};

