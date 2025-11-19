#pragma once
#include "GameObject.h"
#include <corecrt_math_defines.h>

class LitableGameObject : public GameObject
{
protected:
	float litUpTime = 100.0;
	float litUpTimeLeft = 0.0;

	SDL_Texture* spriteTexture = nullptr;
	vector2 spriteDirection = vector2(0, -1); // default up

	virtual void LitUp() {}
	void ResetLitUpTime() {
		litUpTimeLeft = litUpTime;
		LitUp();
	}

private:
	double SpriteDirToAngle() const {
		return std::atan2(spriteDirection.X, -spriteDirection.Y) * 180.0f / static_cast<float>(M_PI);
	}

public:
	LitableGameObject() {
		color = COLOR_WHITE;
		color.A = 0.0;
	}

	void Update(Uint64) override;
	void Draw(SDL_Renderer*) const override;

	void OnCollisionEnter(CollisionResult) override;

	void SetSpriteDirection(vector2 dir) { spriteDirection = dir; }

	bool IsLitUp() const { return litUpTimeLeft > 0; }
	bool IsLitUp(float p) const { return litUpTimeLeft / litUpTime > p; }
};

