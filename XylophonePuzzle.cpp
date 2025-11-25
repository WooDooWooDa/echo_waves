#include "XylophonePuzzle.h"
#include <iostream>
#include "LevelManager.h"
#include "Door.h"

void XylophonePuzzle::Update(Uint64 delta)
{
	if (isPlaying) {
		if (currentNotePlayedIdx >= patterns[currentPatternIdx].length()) {
			isPlaying = false;
			return;
		}

		currentTimeBetweenPlay -= delta;
		if (currentTimeBetweenPlay <= 0) {
			auto x = patterns[currentPatternIdx][currentNotePlayedIdx];
			auto patternXylo = patternXylophones[x];
			if (patternXylo == nullptr) {
				isPlaying = false;
				std::cout << "No pattern xylophone for this note : " << std::toupper(x) << std::endl;
				return;
			}
			patternXylo->Play();

			currentNotePlayedIdx++;
			currentTimeBetweenPlay = timeBetweenPlay;
		}
	}
}

void XylophonePuzzle::RegisterPatternXylophone(char id, Xylophone* newXylo)
{
	patternXylophones.insert({ id, newXylo });
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

void XylophonePuzzle::StartCurrentPattern()
{
	if (patterns.size() <= 0) return;

	isPlaying = true;
	currentTimeBetweenPlay = timeBetweenPlay;
	currentNotePlayedIdx = 0;
}

void XylophonePuzzle::VerifyInputPattern()
{
	auto& pattern = patterns[currentPatternIdx];

	for (size_t i = 0; i < inputPattern.length(); i++)
	{
		if (inputPattern[i] != pattern[i]) {
			inputPattern = "";
			StartCurrentPattern();
			return;
		}
	}

	if (inputPattern != pattern) return;

	CorrectPattern();
}

void XylophonePuzzle::CorrectPattern()
{
	inputPattern = "";
	currentPatternIdx++;
	if (currentPatternIdx < patterns.size()) {
		StartCurrentPattern();
		return;
	}

	solved = true;
	auto doors = LevelManager::GetObjectsOfType<Door>();
	for (auto& door : doors) {
		if (door->doorId == unlockedDoor) {
			door->Unlock();
			break;
		}
	}
}

void XylophonePuzzle::OnXyloPlayed(char xyloId)
{
	if (solved || isPlaying) return;

	if (!hasBeenPlayedOnce) {
		StartCurrentPattern();
		hasBeenPlayedOnce = true;
		return;
	}

	inputPattern.push_back(xyloId);
	VerifyInputPattern();
}
