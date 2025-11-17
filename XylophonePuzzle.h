#pragma once
#include "GameObject.h"
#include "Xylophone.h"

class XylophonePuzzle : public GameObject
{
private:
	bool solved = false;
	bool isPlaying = false;
	bool hasBeenPlayedOnce = false;
	float timeBetweenPlay = 25.0;
	float currentTimeBetweenPlay = 0.0;

	int currentPatternIdx = 0;
	int currentNotePlayedIdx = 0;
	std::vector<std::string> patterns;
	std::unordered_map<char, Xylophone*> patternXylophones;

	std::string inputPattern;
	std::vector<Xylophone*> xylophones;

	char unlockedDoor;
public:
	XylophonePuzzle(char unlockedDoorId) : GameObject() {
		unlockedDoor = unlockedDoorId;
	}

	void Update(Uint64) override;

	void RegisterPatternXylophone(char, Xylophone*);
	void RegisterPlayableXylophone(Xylophone*);
	void AddPattern(std::string const);

	void StartCurrentPattern();
	void VerifyInputPattern();
	void CorrectPattern();

	void OnXyloPlayed(char);
};

