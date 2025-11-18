#include "PianoPuzzle.h"
#include "LevelManager.h"
#include "Door.h"

void PianoPuzzle::RegisterPlayablePiano(Piano* newPiano)
{
	pianos.push_back(newPiano);

	// Creating a lambda capturing "this" so it can be executed with the right obj
	newPiano->OnPlayDelegate = [this]() { VerifyPianos(); };
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
