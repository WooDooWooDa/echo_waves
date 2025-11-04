#pragma once
#include <SDL3/SDL_rect.h>
#include "vector.h"

class GameObject;

struct CollisionResult {
	SDL_FRect intersect;
	GameObject* other;
	vector2 collisionNormal;
};