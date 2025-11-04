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
	vector<std::shared_ptr<GameObject>> levelGameObjects;
	vector2 playerSpawnPosition;

	vector<std::shared_ptr<GameObject>> ConvertLevelTilesDataToGO(LevelData);

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
	vector<std::shared_ptr<GameObject>> GetAllGameObjects() { return levelGameObjects; }
};

