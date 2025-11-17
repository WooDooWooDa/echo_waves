#pragma once
#include <vector>
#include "GameObject.h"
#include "WallTile.h"
#include "LevelFileReader.h"
#include "vector.h"

class LevelManager;

class Level : public GameObject
{
private:
	LevelManager* manager;
	LevelData levelData;
	vector<std::shared_ptr<GameObject>> levelGameObjects;
	vector2 playerSpawnPosition;

	vector<std::shared_ptr<GameObject>> CreateLevelObjsFromData(LevelData);

public:
	Level() = default;
	void SetData(LevelManager* manager, LevelData data);
	void Init() override;
	void Update(Uint64 delta) override;
	void Draw(SDL_Renderer* renderer) const override;

	vector2 GetPlayerSpawn() { return playerSpawnPosition; }
	
	void AddGameObject(std::shared_ptr<GameObject> newObj) {
		levelGameObjects.push_back(newObj);
	}
	void RemoveGameObject(std::shared_ptr<GameObject> objToRemove) {
		auto it = std::find(levelGameObjects.begin(), levelGameObjects.end(), objToRemove);
		if (it != levelGameObjects.end()) {
			levelGameObjects.erase(it);
		}
	}

	const vector<std::shared_ptr<GameObject>>& GetAllGameObjects() const { return levelGameObjects; }
};

