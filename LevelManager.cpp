#include "LevelManager.h"
#include "LevelFileReader.h"

// static member needs a definition (if not declared with "inline" in the .h prior to c++ 17)
//std::shared_ptr<Level> LevelManager::currentLevel = nullptr;

bool LevelManager::LoadAllLevels()
{
	LevelData data = ReadLevelFileData("./assets/level1_" + std::to_string(LEVEL_TILE_COUNT) + ".txt");
	auto newLevel = std::make_shared<Level>();
	newLevel->SetData(this, data);
	levels.push_back(newLevel);

	data = ReadLevelFileData("./assets/level2_" + std::to_string(LEVEL_TILE_COUNT) + ".txt");
	newLevel = std::make_shared<Level>();
	newLevel->SetData(this, data);
	levels.push_back(newLevel);

	nbLevels = levels.size();
	levelLoaded = true;
	return true;
}

Level* LevelManager::GetCurrentLevel()
{
	return currentLevel.get();
}

void LevelManager::SetCurrentLevel(int levelNumber)
{
	if (nbLevels < levelNumber) {
		return;
	}

	currentLevel = GetLevel(levelNumber);
	currentLevel->Init();
}

std::shared_ptr<Level> LevelManager::GetLevel(int levelNumber)
{
	if (nbLevels < levelNumber) {
		return nullptr;
	}

	return levels.at(levelNumber - 1);
}
