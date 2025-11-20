#pragma once
#include <memory>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include "vector.h"
#include "gameSettings.h"
#include "CollisionComponent.h"
#include <vector>

class LevelManager;

class GameObject
{
protected:
	vector2 position;
	vector2 velocity;
	float speed = 0.0;
	vector2 size = 0.0;
	RGBColor color;

	std::vector<std::shared_ptr<CollisionComponent>> colliders;

	bool isDestroyed = false;

public:
	std::string name;
	bool shouldCache = true;
	GameObject() = default;

	virtual void Init();
	virtual void Update(Uint64 delta);
	virtual void Draw(SDL_Renderer* renderer) const;
	void DrawCollider(SDL_Renderer* renderer) const;

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
	CollisionComponent* AddCollider(vector2);
	CollisionComponent* AddCollider(vector2, ECollisionLayer);
	const std::vector<std::shared_ptr<CollisionComponent>>& GetColliders() const { return colliders; }
	virtual void OnTriggerEnter(GameObject* other) {
		// noop
	}

	virtual void OnTriggerStay(GameObject* other) {
		// noop
	}

	virtual void OnTriggerExit(GameObject* other) {
		// noop
	}

	virtual void OnCollisionEnter(CollisionResult res) {
		// noop
	}

	//Life Cycle

	void Destroy() { isDestroyed = true; }
	bool IsDestroyed() { return isDestroyed; }
};

