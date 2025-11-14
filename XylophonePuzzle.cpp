#include "XylophonePuzzle.h"
#include <iostream>
#include "LevelManager.h"
#include "Door.h"

void XylophonePuzzle::Update(Uint64 delta)
{
	if (isPlaying) {
		if (currentIdx > patterns[currentPattern].length()) {
			isPlaying = false;
			return;
		}

		currentTimeBetweenPlay -= delta;
		if (currentTimeBetweenPlay <= 0) {
			auto x = patterns[currentPattern][currentIdx];
			std::cout << "playing" << x << std::endl;

			currentIdx++;
			currentTimeBetweenPlay = timeBetweenPlay;
		}
	}
}

void XylophonePuzzle::RegisterPatternXylophone(Xylophone* newXylo)
{
	patternXylophones.push_back(newXylo);
}

void XylophonePuzzle::RegisterPlayableXylophone(Xylophone* newXylo)
{
	xylophones.push_back(newXylo);

	// Creating a lambda capturing "this" so it can be executed with the right obj
	newXylo->OnPlayDelegate = [this](char xyloId) {
		OnXyloPlayed(xyloId);
	};
	// OR use std::bind
	//newXylo->OnPlayDelegate = std::bind(&XylophonePuzzle::OnXyloPlayed, this, std::placeholders::_1);
}

void XylophonePuzzle::AddPattern(std::string const nextPattern)
{
	patterns.push_back(nextPattern);
}

void XylophonePuzzle::PlayCurrentPattern()
{
	isPlaying = true;
	currentTimeBetweenPlay = timeBetweenPlay;
	currentIdx = 0;
}

void XylophonePuzzle::OnXyloPlayed(char xyloId)
{
	std::cout << xyloId << " played!" << std::endl;
	auto doors = LevelManager::GetObjectsOfType<Door>();
}
