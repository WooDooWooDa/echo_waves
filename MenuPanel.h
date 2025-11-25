#pragma once
#include <SDL3/SDL_render.h>
#include <vector>
#include <memory>
#include "MenuButton.h"
#include "Text.h"

class MenuPanel
{
protected:
	bool isOpen = false;

	//std::vector<std::unique_ptr<MenuButton>> buttons;
	std::vector<Text*> texts;

public:
	MenuPanel() = default;
	virtual ~MenuPanel();
	virtual void Init() = 0;
	virtual void Update(Uint64 delta) = 0;
	virtual void DrawIn(SDL_Renderer* renderer) const = 0;
	void Draw(SDL_Renderer* renderer) const;
	void Hide() { isOpen = false; }
	void Show() { isOpen = true; }
	bool GetVisibility() const { return isOpen; };
};

