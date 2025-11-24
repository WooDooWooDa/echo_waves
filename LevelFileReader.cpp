#include "LevelFileReader.h"

static inline std::string TrimLineEndings(const std::string& str) {
	size_t end = str.find_last_not_of("\r\n");
	return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

// anonymous namespace makes those fonction private to this cpp file
namespace {

	bool AddDirectionIfAny(char tile, string& line, LevelData& data) {
		auto pos = line.find(">");
		if (pos != std::string::npos) {
			char dirChar = line.at(pos + 1);
			vector2 dir;
			switch (dirChar)
			{
			case 'u':
				dir = vector2(0, -1);
				break;
			case 'l':
				dir = vector2(1, 0);
				break;
			case 'd':
				dir = vector2(0, 1);
				break;
			case 'r':
				dir = vector2(-1, 0);
				break;
			}
			data.spriteDirectionPerTile.insert({ tile, dir });
			return true;
		}
		return false;
	}

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

			if (line.starts_with("=unlocks")) {
				getline(levelFile, line);
				data.xylophonePuzzleData.doorUnlocked = line.at(0);
				continue;
			}

			if (line.starts_with("=patterns")){
				readingPatterns = true;
				continue;
			}

			if (readingPatterns) {
				data.xylophonePuzzleData.xylophonePatterns.push_back(line);
				continue;
			}

			data.xylophonePuzzleData.xylophones.push_back({ line.at(0), line.at(1) - '0'});
		}
		return line;
	}

	string ReadPianos(ifstream& levelFile, LevelData& data) {
		string line;
		bool readingPatterns = false;
		while (getline(levelFile, line)) {
			line = TrimLineEndings(line);
			if (line.starts_with("#")) {
				return line;
			}

			if (line.starts_with("=unlocks")) {
				getline(levelFile, line);
				data.pianoPuzzleData.doorUnlocked = line.at(0);
				continue;
			}

			data.pianoPuzzleData.pianos.push_back({ line.at(0), line.at(1) - '0' });
			AddDirectionIfAny(line.at(0), line, data);
		}
		return line;
	}

	string ReadGongs(ifstream& levelFile, LevelData& data) {
		string line;
		bool readingPatterns = false;
		while (getline(levelFile, line)) {
			line = TrimLineEndings(line);
			if (line.starts_with("#")) {
				return line;
			}

			data.gongs.push_back({ line.at(0), line.at(1) });
		}
		return line;
	}

	string ReadTubas(ifstream& levelFile, LevelData& data) {
		string line;
		bool readingPatterns = false;
		while (getline(levelFile, line)) {
			line = TrimLineEndings(line);
			if (line.starts_with("#")) {
				return line;
			}
			data.tubas.push_back(line.at(0));
			AddDirectionIfAny(line.at(0), line, data);
		}
		return line;
	}
}

LevelData ReadLevelFileData(string filename) {
	LevelData levelData;

	ifstream levelFile(GetLevelPath(filename));

	if (!levelFile.is_open()) {
		cerr << "Error opening level file named : " << filename << endl;
		return levelData;
	}

	bool continueReading = true;
	string line;
	getline(levelFile, line);
	line = TrimLineEndings(line);
	while (continueReading) {
		if (line.starts_with("#")) {
			ELevelDataStep step = fileSteps[line];
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
			case PIANO:
				line = ReadPianos(levelFile, levelData);
				break;
			case GONGS:
				line = ReadGongs(levelFile, levelData);
				break;
			case TUBAS:
				line = ReadTubas(levelFile, levelData);
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