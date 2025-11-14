#include "LevelFileReader.h"

static inline std::string TrimLineEndings(const std::string& str) {
	size_t end = str.find_last_not_of("\r\n");
	return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

// anonymous namespace makes those fonction private to this cpp file
namespace {
	string ReadTiles(ifstream& levelFile, LevelData& data) {
		string line;
		while (getline(levelFile, line)) {
			line = TrimLineEndings(line);
			if (line.starts_with("#")) {
				return line;
			}

			if (line.length() != LEVEL_TILE_COUNT) {
				cout << "Invalid level file. Each line must be of length : " << LEVEL_TILE_COUNT << endl;
				return line;
			}

			vector<char> tileLine;
			for (char c : line) {
				tileLine.push_back(c);
			}
			data.tiles.push_back(tileLine);
		}

		if (data.tiles.size() != LEVEL_TILE_COUNT) {
			cout << "Invalid level file. Each col must be of length : " << LEVEL_TILE_COUNT << endl;
			return line;
		}
		return line;
	}

	string ReadDoors(ifstream& levelFile, LevelData& data) {
		string line;
		while (getline(levelFile, line)) {
			line = TrimLineEndings(line);
			if (line.starts_with("#")) {
				return line;
			}

			data.doors.push_back(line.at(0));
		}
		return line;
	}

	string ReadKeys(ifstream& levelFile, LevelData& data) {
		string line;
		while (getline(levelFile, line)) {
			line = TrimLineEndings(line);
			if (line.starts_with("#")) {
				return line;
			}

			data.keys.push_back(line.at(0));
		}
		return line;
	}

	string ReadLinks(ifstream& levelFile, LevelData& data) {
		string line;
		while (getline(levelFile, line)) {
			line = TrimLineEndings(line);
			if (line.starts_with("#")) {
				return line;
			}

			data.DoorNeedKey.insert({ line.at(0), line.at(1) });
		}
		return line;
	}

	string ReadXylophones(ifstream& levelFile, LevelData& data) {
		string line;
		bool readingPatterns = false;
		while (getline(levelFile, line)) {
			line = TrimLineEndings(line);
			if (line.starts_with("#")) {
				return line;
			}

			if (line.starts_with("=patterns")){
				readingPatterns = true;
				continue;
			}

			if (readingPatterns) {
				data.xylophonePatterns.push_back(line);
				continue;
			}

			data.xylophones.push_back(line.at(0));
		}
		return line;
	}
}

LevelData ReadLevelFileData(string filePath) {
	LevelData levelData;

	ifstream levelFile(filePath);

	if (!levelFile.is_open()) {
		cerr << "Error opening level file : " << filePath << endl;
		return levelData;
	}

	bool continueReading = true;
	string line;
	getline(levelFile, line);
	line = TrimLineEndings(line);
	while (continueReading) {
		if (line.starts_with("#")) {
			LevelDataStep step = fileSteps[line];
			switch (step) {
			case TILE:
				line = ReadTiles(levelFile, levelData);
				break;
			case DOORS:
				line = ReadDoors(levelFile, levelData);
				break;
			case KEYS:
				line = ReadKeys(levelFile, levelData);
				break;
			case LINKS:
				line = ReadLinks(levelFile, levelData);
				break;
			case XYLO:
				line = ReadXylophones(levelFile, levelData);
				break;
			case END:
			default:
				continueReading = false;
				break;
			}
		}
		else {
			continueReading = false;
		}
	}

	levelData.success = true;
	return levelData;
}