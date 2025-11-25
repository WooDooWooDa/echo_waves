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
#include "Tuba.h"
#include "LevelExit.h"
#include "Drum.h"
#include "Maracas.h"

static vector2 TileCenter(int j, int i) {
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
			if (c == '.') {
				j++;
				continue;
			}

			shared_ptr<GameObject> newObject = nullptr;
			if (c == 'W' || c == 'w') {
				newObject = make_shared<WallTile>(!std::isupper(c));
			}
			if (c == '@') {
				playerSpawnPosition = TileCenter(j, i);
			}
			if (c == '#') {
				newObject = make_shared<LevelExit>(this);
			}
			if (data.IsTileADoor(c)) {
				bool isDoorHorizontal = std::isupper(c);
				char unlockedBy = data.DoorNeedKey[c];
				newObject = make_shared<Door>(c, isDoorHorizontal, unlockedBy);
			}
			if (data.IsTileAKey(c)) {
				newObject = make_shared<Key>(c);
			}
			if (int note; data.IsTileAXylophone(c, note)) {
				auto newXylo = make_shared<Xylophone>(c, note);
				newXylo->MoveTo(TileCenter(j, i));

				auto puzzle = FindOrCreateXylophonePuzzle(levelGOs, data);
				if (isupper(c)) {
					puzzle->RegisterPlayableXylophone(newXylo.get());
				}
				else {
					puzzle->RegisterPatternXylophone(std::toupper(c), newXylo.get());
				}
				newObject = newXylo;
			}
			if (int note; data.IsTileAPiano(c, note)) {
				newObject = make_shared<Piano>(c, isupper(c) ? 0 : note, note);

				if (isupper(c)) {
					auto puzzle = FindOrCreatePianoPuzzle(levelGOs, data);
					puzzle->RegisterPlayablePiano(newObject.get());
				}
			}
			if (char door; data.IsTileAGong(c, door)) {
				newObject = make_shared<Gong>(c, door);
			}
			if (data.IsTileATuba(c)) {
				newObject = make_shared<Tuba>(c);
			}
			if (char door; data.IsTileADrum(c, door)) {
				newObject = make_shared<Drum>(c, door);
			}
			if (data.IsTileAMaracas(c)) {
				newObject = make_shared<Maracas>(c);
			}

			// Handle new object
			if (newObject) {
				newObject->MoveTo(TileCenter(j, i));
				levelGOs.push_back(newObject);
				auto litable = dynamic_cast<LitableGameObject*>(newObject.get());
				if (vector2 dir; litable && data.HasASpriteDirection(c, dir)) {
					litable->SetSpriteDirection(dir);
				}
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
	auto objects = levelGameObjects;
	for (auto& obj : objects) {
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

void Level::Destroy()
{
	levelGameObjects.clear();
}
