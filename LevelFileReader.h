#pragma once
#include "gameSettings.h"
#include "SDL3/SDL.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

enum LevelDataStep {
	TILE,
	DOORS,
	KEYS,
	LINKS,
	END
};

static unordered_map<string, LevelDataStep> fileSteps = {
	{"#tile", TILE},
	{"#doors", DOORS},
	{"#keys", KEYS},
	{"#key_door_links", LINKS},
	{"#end", END}
};

struct LevelData {
	bool success;
	vector<vector<char>> tiles;
	vector<char> doors;
	vector<char> keys;
	unordered_map<char, char> keyToDoor;

	bool IsTileADoor(char tile) {
		return std::find(doors.begin(), doors.end(), tile) != doors.end();
	}

	bool IsTileAKey(char tile) {
		return std::find(keys.begin(), keys.end(), tile) != keys.end();
	}
};

// This fonction is public to the .h file and from who includes it
LevelData ReadLevelFileData(string filePath);