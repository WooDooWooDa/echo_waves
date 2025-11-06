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
	RGBColor color;

	CollisionComponent collision;

	bool isDestroyed = false;

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

	//Collision
	CollisionComponent& GetCollider() { return collision; }
	virtual void OnTriggerEnter(GameObject* other) {
		// custom behavior for triggers
	}
	virtual void OnCollisionEnter(CollisionResult res) {
		// custom behavior for collisions
	}

	//Life Cycle
	void Destroy() { isDestroyed = true; }
	bool IsDestroyed() { return isDestroyed; }
};

