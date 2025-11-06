#pragma once
#include "Level.h"
#include "CollisionLayers.h"
#include "CollisionResult.h"

class CollisionSystem
{
	bool isInit = false;
	bool CollisionMatrix[LCount][LCount] = {};
	//CollisionEventQueue collisionEvents;

	void ResolveCollision(GameObject&, CollisionResult&);

	bool ShouldCollide(ECollisionLayer a, ECollisionLayer b) {
		if (!isInit) InitCollisionMatrix();
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

		CollisionMatrix[LSoundParticle][LWall] = true;
		CollisionMatrix[LSoundParticle][LObject] = true;
		CollisionMatrix[LSoundParticle][LPlayer] = false;
		isInit = true;
	}

	void CheckCollision(Level*);
};

