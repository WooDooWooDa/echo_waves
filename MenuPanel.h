#pragma once
#include <SDL3/SDL_render.h>
#include <vector>
#include "MenuButton.h"
#include <memory>

class MenuPanel
{
private:
	bool isOpen = false;

	std::vector<std::unique_ptr<MenuButton>> buttons;

public:
	virtual void Update(Uint64 delta);
	virtual void Draw(SDL_Renderer* renderer) const;
};

