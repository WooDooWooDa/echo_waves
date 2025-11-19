#include "Level.h"
#include "LevelFileReader.h"
#include "LevelManager.h"
#include "Door.h"
#include "Key.h"
#include "Xylophone.h"
#include "XylophonePuzzle.h"
#include "Piano.h"
#include "PianoPuzzle.h"
#include "Gong.h"

vector2 TileCenter(int j, int i) {
	return vector2(j * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2,
		i * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2);
}

XylophonePuzzle* FindOrCreateXylophonePuzzle(vector<std::shared_ptr<GameObject>>& objs, LevelData& data) {
	auto found = std::find_if(objs.begin(), objs.end(), [](const std::shared_ptr<GameObject>& obj) {
		return dynamic_cast<XylophonePuzzle*>(obj.get()) != nullptr;
		});
	if (found != objs.end()) {
		return dynamic_cast<XylophonePuzzle*>(found->get());
	}

	auto newPuzzle = make_shared<XylophonePuzzle>(data.xylophonePuzzleData.doorUnlocked);
	for (auto& pattern : data.xylophonePuzzleData.xylophonePatterns) {
		newPuzzle->AddPattern(pattern);
	}
	objs.push_back(newPuzzle);
	return newPuzzle.get();
}

PianoPuzzle* FindOrCreatePianoPuzzle(vector<std::shared_ptr<GameObject>>& objs, LevelData& data) {
	auto found = std::find_if(objs.begin(), objs.end(), [](const std::shared_ptr<GameObject>& obj) {
		return dynamic_cast<PianoPuzzle*>(obj.get()) != nullptr;
		});
	if (found != objs.end()) {
		return dynamic_cast<PianoPuzzle*>(found->get());
	}

	auto newPuzzle = make_shared<PianoPuzzle>(data.pianoPuzzleData.doorUnlocked);
	objs.push_back(newPuzzle);
	return newPuzzle.get();
}

vector<std::shared_ptr<GameObject>> Level::CreateLevelObjsFromData(LevelData data)
{
	vector<std::shared_ptr<GameObject>> levelGOs;
	int i = 0;
	int j = 0;
	for (vector<char> line : data.tiles) {
		j = 0;
		for (char c : line) {
			// WallTile
			if (c == 'W' || c == 'w') {
				auto newWall = make_shared<WallTile>(!std::isupper(c));
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
			int note;
			if (data.IsTileAXylophone(c, note)) {
				auto newXylo = make_shared<Xylophone>(c, note);
				newXylo->MoveTo(TileCenter(j, i));
				levelGOs.push_back(newXylo);

				auto puzzle = FindOrCreateXylophonePuzzle(levelGOs, data);
				if (isupper(c)) {
					puzzle->RegisterPlayableXylophone(newXylo.get());
				}
				else {
					puzzle->RegisterPatternXylophone(std::toupper(c), newXylo.get());
				}
			}
			if (data.IsTileAPiano(c, note)) {
				auto newPiano = make_shared<Piano>(c, isupper(c) ? 0 : note, note);
				newPiano->MoveTo(TileCenter(j, i));
				levelGOs.push_back(newPiano);

				if (isupper(c)) {
					auto puzzle = FindOrCreatePianoPuzzle(levelGOs, data);
					puzzle->RegisterPlayablePiano(newPiano.get());
				}
			}
			char door;
			if (data.IsTileAGong(c, door)) {
				auto newGong = make_shared<Gong>(c, door);
				newGong->MoveTo(TileCenter(j, i));
				levelGOs.push_back(newGong);
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
	this->levelData = data;
}

void Level::Init() {
	levelGameObjects.clear();

	levelGameObjects = CreateLevelObjsFromData(levelData);

	for (auto& obj : levelGameObjects) {
		obj->Init();
		//accGrid.Insert(obj.get());
	}
}

void Level::Update(Uint64 delta)
{
	// Update acc grid, before collision
	/*for (auto& obj : levelGameObjects) {
		accGrid.Update(obj.get());
	}*/

	// Check collision
	collisionSystem.CheckCollision(this);

	// Update all level objects
	for (auto& obj : levelGameObjects) {
		obj->Update(delta);
	}

	// Clean up all destroyed objects
	auto objToRemove = std::remove_if(levelGameObjects.begin(), levelGameObjects.end(),
		[](const std::shared_ptr<GameObject>& obj) {
			return obj->IsDestroyed();
		});
	
	if (objToRemove == levelGameObjects.end()) return;

	/*for (auto it = objToRemove; it != levelGameObjects.end(); ++it) {
		accGrid.Remove(it->get());
	}*/
	levelGameObjects.erase(objToRemove, levelGameObjects.end());
}

void Level::Draw(SDL_Renderer* renderer) const
{
	for (auto& obj : levelGameObjects) {
		obj->Draw(renderer);
	}
}
