#include "MenuPanel.h"

MenuPanel::~MenuPanel()
{
	for (auto& text : texts) {
		delete text;
	}
}

void MenuPanel::Draw(SDL_Renderer* renderer) const
{
	if (isOpen) {
		DrawIn(renderer);
	}
}
