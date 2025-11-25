#pragma once
#include "gameSettings.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include "vector.h"

using namespace std;

enum ELevelDataStep {
	TILE,
	DOORS,
	KEYS,
	LINKS,
	XYLO,
	PIANO,
	GONGS,
	TUBAS,
	DRUMS,
	MARACAS,
	END
};

static unordered_map<string, ELevelDataStep> fileSteps = {
	{"#tile", TILE},
	{"#doors", DOORS},
	{"#keys", KEYS},
	{"#door_key_links", LINKS},
	{"#xylophones", XYLO},
	{"#pianos", PIANO},
	{"#gongs", 	GONGS},
	{"#tubas", TUBAS},
	{"#drums", DRUMS},
	{"#maracas", MARACAS},
	{"#end", END}
};

struct XylophonePuzzleData {
	vector<pair<char, int>> xylophones;
	vector<string> xylophonePatterns;
	char doorUnlocked;
};

struct PianoPuzzleData {
	vector<pair<char, int>> pianos;
	vector<string> solution;
	char doorUnlocked;
};

struct LevelData {
	bool success;
	vector<vector<char>> tiles;
	vector<char> doors;
	vector<char> keys;
	XylophonePuzzleData xylophonePuzzleData;
	PianoPuzzleData pianoPuzzleData;
	vector<pair<char, char>> gongs;
	vector<char> tubas;
	vector<pair<char, char>> drums;
	vector<char> maracas;
	unordered_map<char, char> DoorNeedKey;
	unordered_map<char, vector2> spriteDirectionPerTile;

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

	bool IsTileAPiano(char tile, int& solutionNote) {
		for (auto& pianoPair : pianoPuzzleData.pianos) {
			if (pianoPair.first == toupper(tile)) {
				solutionNote = pianoPair.second;
				return true;
			}
		}
		return false;
	}

	bool IsTileAGong(char tile, char& door) {
		for (auto& gong : gongs) {
			if (gong.first == tile) {
				door = gong.second;
				return true;
			}
		}
		return false;
	}

	bool IsTileATuba(char tile) {
		return std::find(tubas.begin(), tubas.end(), tile) != tubas.end();
	}

	bool IsTileADrum(char tile, char& door) {
		for (auto& drum : drums) {
			if (drum.first == tile) {
				door = drum.second;
				return true;
			}
		}
		return false;
	}
	
	bool IsTileAMaracas(char tile) {
		return std::find(maracas.begin(), maracas.end(), tile) != maracas.end();
	}

	bool HasASpriteDirection(char tile, vector2& dir) {
		auto found = spriteDirectionPerTile.find(tile);
		if (found != spriteDirectionPerTile.end()) {
			dir = found->second;
			return true;
		}
		return false;
	}
};

static std::string GetLevelPath(const std::string& relativePath)
{
#ifdef __EMSCRIPTEN__
	return "/assets/levels/" + relativePath + ".txt";  // Matches embedded path
#else
	return "./assets/levels/" + relativePath + ".txt";
#endif
}

// This fonction is public to the .h file and from who includes it
LevelData ReadLevelFileData(string filename);