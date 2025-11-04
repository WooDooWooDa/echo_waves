#pragma once
#include <vector>
#include "GameObject.h"
#include "WallTile.h"
#include "LevelFileReader.h"

class LevelManager;

class Level : public GameObject
{
private:
	LevelManager* manager;
	vector<std::shared_ptr<GameObject>> levelGameObjects;

	static vector<std::shared_ptr<GameObject>> ConvertLevelTilesDataToGO(LevelData data) {
		vector<std::shared_ptr<GameObject>> levelGOs;
		int i = 0;
		int j = 0;
		for (vector<char> line : data.tiles) {
			j = 0;
			for (char c : line) {
				// WallTile
				std::cout << c;
				if (c == '1') {
					auto newWall = make_shared<WallTile>();
					newWall->MoveTo(j * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2,
						i * LEVEL_TILE_SIZE + LEVEL_TILE_SIZE / 2);
					levelGOs.push_back(newWall);
				}
				j++;
			}
			i++;
			std::cout << std::endl;
		}
		return levelGOs;
	}

public:
	Level() = default;
	void SetData(LevelManager* manager, LevelData data);
	void Init() override;
	void Update(Uint64 delta) override;
	void Draw(SDL_Renderer* renderer) const override;

	void AddGameObject(std::shared_ptr<GameObject> newObj) {
		levelGameObjects.push_back(newObj);
	}
	vector<std::shared_ptr<GameObject>> GetAllGameObjects() { return levelGameObjects; }
};

