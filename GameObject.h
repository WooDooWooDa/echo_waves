#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include "vector.h"

class GameObject
{
protected:
	vector2 position;
	vector2 velocity;
	float speed = 5.0;
	SDL_FRect bounds;
	float size = 50.0;
	vector3 color;

public:
	GameObject() = default; // allow default construction

	virtual void Init();
	virtual void Update(Uint64 delta);
	virtual void Draw(SDL_Renderer* renderer) const;
	
	void SetVelocityX(float x);
	void SetVelocityY(float y);

	void Move(float x, float y);
	void Move(vector2 vec);
};

