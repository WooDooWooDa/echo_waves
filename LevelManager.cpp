#include "LevelManager.h"
#include "LevelFileReader.h"

bool LevelManager::LoadAllLevels()
{
	LevelData data = ReadLevelFileData("./assets/level1.txt");
	auto newLevel = std::make_shared<Level>();
	newLevel->SetData(this, data);
	newLevel->Init();
	levels.push_back(newLevel);

	data = ReadLevelFileData("./assets/level2.txt");
	newLevel = std::make_shared<Level>();
	newLevel->SetData(this, data);
	newLevel->Init();
	levels.push_back(newLevel);

	nbLevels = levels.size();
	levelLoaded = true;
	return true;
}

void LevelManager::SetCurrentLevel(int levelNumber)
{
	if (nbLevels < levelNumber) {
		return;
	}

	currentLevel = levels.at(levelNumber - 1);
}

std::shared_ptr<Level> LevelManager::GetLevel(int levelNumber)
{
	if (nbLevels < levelNumber) {
		return nullptr;
	}

	return levels.at(levelNumber - 1);
}
