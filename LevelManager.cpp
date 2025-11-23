#include "LevelManager.h"
#include "LevelFileReader.h"

// static member needs a definition (if not declared with "inline" in the .h prior to c++ 17)
//std::shared_ptr<Level> LevelManager::currentLevel = nullptr;

static std::string GetLevelPath(const std::string& relativePath)
{
#ifdef __EMSCRIPTEN__
	return "/assets/levels/" + relativePath + ".txt";  // Matches embedded path
#else
	return "./assets/levels/" + relativePath + ".txt";
#endif
}

Level* LevelManager::LoadSpecialLevel(string name) {
	if (currentLevel) {
		currentLevel->Destroy();
	}
	InvalidateCache();

	LevelData data = ReadLevelFileData(GetLevelPath(name));
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
		data = ReadLevelFileData(GetLevelPath("level" + std::to_string(i) + "_" + std::to_string(LEVEL_TILE_COUNT)));
		newLevel = std::make_shared<Level>();
		newLevel->SetData(this, data);
		levels.push_back(newLevel);
	}

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
