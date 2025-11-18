#pragma once
#include "GameObject.h"
#include "Piano.h"

class PianoPuzzle : public GameObject
{
private:
	bool isSolved = false;
	std::vector<Piano*> pianos;

	char unlockedDoor;
public:
	PianoPuzzle(char doorUnlocked) {
		unlockedDoor = doorUnlocked;
	}

	void RegisterPlayablePiano(Piano*);
	void VerifyPianos();
	void CorrectSolution();
};

