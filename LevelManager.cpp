#include "LevelManager.h"
#include "LevelFileReader.h"

// static member needs a definition (if not declared with "inline" in the .h prior to c++ 17)
//std::shared_ptr<Level> LevelManager::currentLevel = nullptr;

Level* LevelManager::LoadAndInitSpecialLevel(string name) {
	if (currentLevel) {
		currentLevel->Destroy();
	}
	InvalidateCache();

	LevelData data = ReadLevelFileData(name);
	auto newLevel = std::make_shared<Level>();
	newLevel->SetData(this, data);
	currentLevel = newLevel;
	currentLevel->Init();
	return newLevel.get();
}

bool LevelManager::LoadAllLevels()
{
	LevelData data;
	shared_ptr<Level> newLevel;
	for (int i = 1; i <= nbLevels; i++)
	{
		data = ReadLevelFileData("level" + std::to_string(i));
		newLevel = std::make_shared<Level>();
		newLevel->SetData(this, data);
		levels.push_back(newLevel);
	}

	levelLoaded = true;
	return true;
}

Level* LevelManager::GetCurrentLevel() const
{
	return currentLevel.get();
}

void LevelManager::SetCurrentLevel(int levelNumber)
{
	if (nbLevels < levelNumber) {
		return;
	}

	if (currentLevel) {
		currentLevel->Destroy();
	}

	InvalidateCache();

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
