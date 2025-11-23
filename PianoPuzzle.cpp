#include "PianoPuzzle.h"
#include "LevelManager.h"
#include "Door.h"

void PianoPuzzle::RegisterPlayablePiano(GameObject * newPiano)
{
	auto piano = dynamic_cast<Piano*>(newPiano);
	pianos.push_back(piano);

	// Creating a lambda capturing "this" so it can be executed with the right obj
	piano->OnPlayDelegate = [this](char) { VerifyPianos(); };
}

void PianoPuzzle::VerifyPianos()
{
	if (isSolved) return;

	for (auto& piano : pianos) {
		if (!piano->HasSolutionNote()) return;
	}

	CorrectSolution();
}

void PianoPuzzle::CorrectSolution()
{
	isSolved = true;

	auto doors = LevelManager::GetObjectsOfType<Door>();
	for (auto& door : doors) {
		if (door->doorId == unlockedDoor) {
			door->Unlock();
			break;
		}
	}
}
