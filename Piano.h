#pragma once
#include "LitableGameObject.h"
#include "IInteractable.h"
#include <functional>

constexpr int NB_PIANO_NOTES = 5;

class Piano : public LitableGameObject, public IInteractable
{
	char pianoId;
	bool isHover = false;

	int solutionNote;
	int currentNote;
	SDL_Texture* pianoTextures[NB_PIANO_NOTES] = {};

public:
	std::function<void()> OnPlayDelegate;

	Piano(char id, int startingNote, int solution) : LitableGameObject() {
		pianoId = id;
		name = "Piano";
		size = vector2(LEVEL_TILE_SIZE / 1.5);
		litUpTime = 200;
		currentNote = startingNote;
		solutionNote = solution;

		AddCollider(size, ECollisionLayer::LWall);
		AddCollider(vector2(LEVEL_TILE_SIZE), ECollisionLayer::LInteraction)->isTrigger = true;
	}

	void Init() override;
	void Draw(SDL_Renderer*) const override;

	void UnHover() override;
	void Hover() override;
	void Interact(GameObject*) override;

	bool HasSolutionNote() const { return currentNote == solutionNote; }
	void ChangeNote();
	void Play();
};

