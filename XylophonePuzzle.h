#pragma once
#include "GameObject.h"
#include "Xylophone.h"

class XylophonePuzzle : public GameObject
{
private:
	bool isPlaying = false;
	float timeBetweenPlay = 50.0;
	float currentTimeBetweenPlay = 0.0;

	int currentPattern = 0;
	int currentIdx = 0;
	std::vector<std::string> patterns;
	std::vector<Xylophone*> patternXylophones;

	std::vector<Xylophone*> xylophones;

public:
	XylophonePuzzle() = default;

	void Update(Uint64) override;

	void RegisterPatternXylophone(Xylophone*);
	void RegisterXylophone(Xylophone*);
	void AddPattern(std::string const);

	void PlayCurrentPattern();

	void OnXyloPlayed(char);
};

