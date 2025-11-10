#pragma once
#include "GameObject.h"

class LitableGameObject : public GameObject
{
protected:
	float litUpTime = 200.0;
	float litUpTimeLeft = 0.0;

	SDL_Texture* spriteTexture;

	virtual void LitUp() {}
	void ResetLitUpTime() {
		litUpTimeLeft = litUpTime;
		LitUp();
	}

public:
	LitableGameObject() {
		color = COLOR_WHITE;
		color.A = 0.0;
	}

	void Update(Uint64) override;
	void Draw(SDL_Renderer*) const override;

	void OnCollisionEnter(CollisionResult) override;

	bool IsLitUp() const { return litUpTimeLeft > 0; }
};

