#pragma once
#include "Instrument.h"
#include "IInteractable.h"
#include <functional>

constexpr int NB_PIANO_NOTES = 5;

class Piano : public Instrument
{
	int solutionNote;
	int currentNote;
	SDL_Texture* pianoTextures[NB_PIANO_NOTES] = {};

public:
	Piano(char id, int startingNote, int solution) : Instrument(id) {
		name = "Piano";
		currentNote = startingNote;
		solutionNote = solution;
		isPlayable = startingNote == 0;

		AddCollider(size, ECollisionLayer::LWall);
	}

	void Init() override;
	bool HasSolutionNote() const { return currentNote == solutionNote; }
	void ChangeNote();

	void Play() override;
};

