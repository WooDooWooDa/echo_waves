#pragma once
#include "gameSettings.h"
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
	XYLO,
	END
};

static unordered_map<string, LevelDataStep> fileSteps = {
	{"#tile", TILE},
	{"#doors", DOORS},
	{"#keys", KEYS},
	{"#door_key_links", LINKS},
	{"#xylophones", XYLO},
	{"#end", END}
};

struct LevelData {
	bool success;
	vector<vector<char>> tiles;
	vector<char> doors;
	vector<char> keys;
	vector<char> xylophones;
	vector<string> xylophonePatterns;
	unordered_map<char, char> DoorNeedKey;

	bool IsTileADoor(char tile) {
		return std::find(doors.begin(), doors.end(), tile) != doors.end();
	}

	bool IsTileAKey(char tile) {
		return std::find(keys.begin(), keys.end(), tile) != keys.end();
	}

	bool IsTileAXylophone(char tile) {
		return std::find(xylophones.begin(), xylophones.end(), std::toupper(tile)) != xylophones.end();
	}
};

// This fonction is public to the .h file and from who includes it
LevelData ReadLevelFileData(string filePath);