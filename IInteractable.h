#pragma once

class IInteractable {
public:
	virtual void Hover() = 0;
	virtual void UnHover() = 0;
	virtual void Interact(GameObject*) = 0;
};