#pragma once
#include <vector>
#include "GameObject.h"
#include "CollisionSystem.h"
#include "WallTile.h"
#include "LevelFileReader.h"
#include "vector.h"
#include "AccelerationGrid.h"

class LevelManager;

class Level : public GameObject
{
private:
	LevelManager* manager = nullptr;
	LevelData levelData;
	vector<std::shared_ptr<GameObject>> levelGameObjects;

	CollisionSystem collisionSystem;
	AccelerationGrid accGrid;

	vector2 playerSpawnPosition;

	vector<std::shared_ptr<GameObject>> CreateLevelObjsFromData(LevelData);

public:
	Level() : accGrid(LEVEL_TILE_SIZE) {}

	void SetData(LevelManager* manager, LevelData data);
	void Init() override;
	void Update(Uint64 delta) override;
	void Draw(SDL_Renderer* renderer) const override;

	const AccelerationGrid& GetGrid() const { return accGrid; }
	const vector2 GetPlayerSpawn() const { return playerSpawnPosition; }
	
	void AddGameObject(std::shared_ptr<GameObject> newObj) {
		levelGameObjects.push_back(newObj);
		//accGrid.Insert(newObj.get());
	}
	void RemoveGameObject(std::shared_ptr<GameObject> objToRemove) {
		//accGrid.Remove(objToRemove.get());
		auto it = std::find(levelGameObjects.begin(), levelGameObjects.end(), objToRemove);
		if (it != levelGameObjects.end()) {
			levelGameObjects.erase(it);
		}
	}

	const vector<std::shared_ptr<GameObject>>& GetAllGameObjects() const { return levelGameObjects; }
};

