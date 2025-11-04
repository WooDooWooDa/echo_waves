#pragma once
#include <vector>
#include "Level.h"

class LevelManager
{
private:
	bool levelLoaded = false;
	int nbLevels;
	std::shared_ptr<Level> currentLevel;
	std::vector<std::shared_ptr<Level>> levels;

public:
	bool LoadAllLevels();
	void SetCurrentLevel(int);
	std::shared_ptr<Level> GetLevel(int levelNumber);
};

