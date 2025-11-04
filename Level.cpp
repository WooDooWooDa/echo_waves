#include "Level.h"
#include "LevelFileReader.h"
#include "LevelManager.h"

vector<std::shared_ptr<GameObject>> Level::ConvertLevelTilesDataToGO(LevelData data)
{
	vector<std::shared_ptr<GameObject>> levelGOs;
	int i = 0;
	int j = 0;
	for (vector<char> line : data.tiles) {
		j = 0;
		for (char c : line) {
			// WallTile
			std::cout << c;
			if (c == 'W') {
				auto newWall = make_shared<WallTile>();
				newWall->MoveTo(j * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2,
					i * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2);
				levelGOs.push_back(newWall);
			}
			if (c == 'P') {
				playerSpawnPosition = vector2(j * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2,
					i * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2);
			}
			j++;
		}
		i++;
		std::cout << std::endl;
	}
	return levelGOs;
}

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
