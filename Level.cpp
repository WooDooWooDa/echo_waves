#include "Level.h"
#include "LevelFileReader.h"
#include "LevelManager.h"

void Level::SetData(LevelManager* manager, LevelData data)
{
	manager = manager;
	auto GOs = ConvertLevelTilesDataToGO(data);
	levelGameObjects = GOs;
}

void Level::Init() {
	for (auto obj : levelGameObjects) {
		obj->Init();
	}
}

void Level::Update(Uint64 delta)
{
	for (auto obj : levelGameObjects) {
		obj->Update(delta);
	}
}

void Level::Draw(SDL_Renderer* renderer) const
{
	for (auto obj : levelGameObjects) {
		obj->Draw(renderer);
	}
}
