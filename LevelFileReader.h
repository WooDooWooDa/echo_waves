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

struct XylophonePuzzleData {
	vector<pair<char, int>> xylophones;
	vector<string> xylophonePatterns;
	char doorUnlocked;
};

struct LevelData {
	bool success;
	vector<vector<char>> tiles;
	vector<char> doors;
	vector<char> keys;
	XylophonePuzzleData xylophonePuzzleData;
	unordered_map<char, char> DoorNeedKey;

	bool IsTileADoor(char tile) {
		return std::find(doors.begin(), doors.end(), tile) != doors.end();
	}

	bool IsTileAKey(char tile) {
		return std::find(keys.begin(), keys.end(), tile) != keys.end();
	}

	bool IsTileAXylophone(char tile, int& note) {
		for (auto& xyloPair : xylophonePuzzleData.xylophones) {
			if (xyloPair.first == toupper(tile)) {
				note = xyloPair.second;
				return true;
			}
		}
		return false;
	}
};

// This fonction is public to the .h file and from who includes it
LevelData ReadLevelFileData(string filePath);