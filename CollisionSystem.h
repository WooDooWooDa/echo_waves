#pragma once
#include "Level.h"
#include "CollisionLayers.h"

class CollisionSystem
{
	bool isInit = false;
	bool CollisionMatrix[LCount][LCount] = {};
	//CollisionEventQueue collisionEvents;

	void ResolveCollision(GameObject&, SDL_FRect&);

	bool ShouldCollide(ECollisionLayer a, ECollisionLayer b) {
		return CollisionMatrix[a][b];
	}

public:
	CollisionSystem() {
		InitCollisionMatrix();
	}

	/*void ResolveAllEvents() {
		collisionEvents.ExecuteAll();
	}*/

	void InitCollisionMatrix() {
		CollisionMatrix[LPlayer][LWall] = true;
		CollisionMatrix[LPlayer][LObject] = true;

		CollisionMatrix[LWall][LPlayer] = false;
		CollisionMatrix[LWall][LWall] = false;

		CollisionMatrix[LObject][LPlayer] = true;
		CollisionMatrix[LObject][LWall] = true;
		CollisionMatrix[LObject][LObject] = false;

		CollisionMatrix[LWave][LWall] = true;
		CollisionMatrix[LWave][LObject] = true;
		isInit = true;
	}

	void CheckCollision(std::shared_ptr<Level>);
};

