#pragma once
#include <functional>
#include "vector.h"
#include <SDL3/SDL_render.h>

class MenuButton
{
private:
	vector2 position;
	std::string text;

public:
	std::function<void()> OnClick;

	MenuButton(vector2 pos, std::string text, std::function<void()> onClickEvent) {
		position = position;
		this->text = text;
		OnClick = onClickEvent;
	}

	virtual void Draw(SDL_Renderer* renderer) const;
};

