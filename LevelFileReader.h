#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "gameSettings.h"
#include "GameObject.h"
#include "SDL3/SDL.h"
#include "WallTile.h"
using namespace std;

struct LevelData {
	bool success;
	vector<vector<char>> tiles;
};

static LevelData ReadLevelFileData(string filePath) {
	LevelData levelData;

	ifstream levelFile(filePath);
	
	if (!levelFile.is_open()) {
		cerr << "Error opening level file : " << filePath << endl;
		return levelData;
	}

	string line;
	while (getline(levelFile, line)) {

		if (line.length() < LEVEL_TILE_COUNT) {
			cerr << "Invalid level file. Each line must be of length : " << LEVEL_TILE_COUNT << endl;
			return levelData;
		}

		vector<char> tileLine;
		for (char c : line) {
			tileLine.push_back(c);
		}
		levelData.tiles.push_back(tileLine);
	}

	if (levelData.tiles.size() < LEVEL_TILE_COUNT) {
		cerr << "Invalid level file. Each col must be of length : " << LEVEL_TILE_COUNT << endl;
		return levelData;
	}
	//SDL_CloseIO(file);

	levelData.success = true;
	return levelData;
}