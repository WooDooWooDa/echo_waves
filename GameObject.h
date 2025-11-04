#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include "vector.h"
#include "gameSettings.h"
#include "CollisionComponent.h"

class GameObject
{
protected:
	vector2 position;
	vector2 velocity;
	float speed = 0.0;
	float size = 0.0;
	vector3 color;

	CollisionComponent collision;

public:
	GameObject() {
		collision.SetOwner(this);
	}

	virtual void Init();
	virtual void Update(Uint64 delta);
	virtual void Draw(SDL_Renderer* renderer) const;

	vector2 GetPosition() const {
		return position;
	}

	void SetVelocityX(float x);
	void SetVelocityY(float y);

	void MoveTo(float x, float y);
	void MoveTo(vector2 vec);
	void MoveBy(float x, float y);
	void MoveBy(vector2 vec);

	SDL_FRect GetBounds() const;
	void BoundPositionToScreenSize();

	CollisionComponent& GetCollider() { return collision; }
	virtual void OnTriggerEnter(GameObject* other) {
		// custom behavior for triggers
	}
	virtual void OnCollisionEnter(GameObject* other) {
		// custom behavior for collisions
	}
};

