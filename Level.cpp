#include "Level.h"
#include "LevelFileReader.h"
#include "LevelManager.h"
#include "Door.h"
#include "Key.h"

vector2 TileCenter(int j, int i) {
	return vector2(j * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2,
		i * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2);
}

vector<std::shared_ptr<GameObject>> Level::ConvertLevelTilesDataToGO(LevelData data)
{
	vector<std::shared_ptr<GameObject>> levelGOs;
	int i = 0;
	int j = 0;
	for (vector<char> line : data.tiles) {
		j = 0;
		for (char c : line) {
			// WallTile
			if (c == 'W') {
				auto newWall = make_shared<WallTile>();
				newWall->MoveTo(TileCenter(j, i));
				levelGOs.push_back(newWall);
			}
			if (c == 'P') {
				playerSpawnPosition = TileCenter(j, i);
			}
			if (data.IsTileADoor(c)) {
				bool isDoorHorizontal = std::isupper(c);
				char unlockedBy = data.DoorNeedKey[c];
				auto newDoor = make_shared<Door>(c, isDoorHorizontal, unlockedBy);
				newDoor->MoveTo(TileCenter(j, i));
				levelGOs.push_back(newDoor);
			}
			if (data.IsTileAKey(c)) {
				auto newKey = make_shared<Key>(c);
				newKey->MoveTo(TileCenter(j, i));
				levelGOs.push_back(newKey);
			}
			j++;
		}
		i++;
	}
	return levelGOs;
}

void Level::SetData(LevelManager* manager, LevelData data)
{
	this->manager = manager;
	auto GOs = ConvertLevelTilesDataToGO(data);
	levelGameObjects = GOs;
}

void Level::Init() {
	for (auto& obj : levelGameObjects) {
		obj->Init();
	}
}

void Level::Update(Uint64 delta)
{
	// Update all level objects
	for (auto& obj : levelGameObjects) {
		obj->Update(delta);
	}

	// Clean up all destroyed objects
	levelGameObjects.erase(
		std::remove_if(levelGameObjects.begin(), levelGameObjects.end(),
			[](const std::shared_ptr<GameObject>& obj) {
				return obj->IsDestroyed();
			}),
		levelGameObjects.end());
}

void Level::Draw(SDL_Renderer* renderer) const
{
	for (auto& obj : levelGameObjects) {
		obj->Draw(renderer);
	}
}
