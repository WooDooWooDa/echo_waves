#pragma once
#include <vector>
#include "Level.h"

class LevelManager
{
private:
	// inline declaration & definition, possible with c++ 17
	inline static std::shared_ptr<Level> currentLevel = nullptr;

	bool levelLoaded = false;
	int nbLevels;
	std::vector<std::shared_ptr<Level>> levels;

public:
	bool LoadAllLevels();
	Level* GetCurrentLevel();
	void SetCurrentLevel(int);
	std::shared_ptr<Level> GetLevel(int levelNumber);

	static void AddGameObjectToLevel(std::shared_ptr<GameObject> obj) {
		if (currentLevel != nullptr) {
			currentLevel->AddGameObject(obj);
		}
	}

	static void RemoveGameObjectFromLevel(std::shared_ptr<GameObject> obj) {
		if (currentLevel != nullptr) {
			currentLevel->RemoveGameObject(obj);
		}
	}
};

