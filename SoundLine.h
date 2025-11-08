#pragma once
#include "GameObject.h"

class SoundLine : public GameObject
{
private:
	vector2 normal;
	float maxStrength;
	float currentStrength;

public:
	SoundLine(vector2 normal, float strength) : GameObject() {
		this->normal = normal;
		maxStrength = strength;
		currentStrength = maxStrength;
		color = COLOR_WHITE;
	}

	void Update(Uint64 delta) override;
	void Draw(SDL_Renderer*) const override;
};

