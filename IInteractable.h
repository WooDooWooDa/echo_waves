#pragma once

class IInteractable {
public:
	virtual void Hover() = 0;
	virtual void UnHover() = 0;
	virtual void Interact(GameObject*) = 0;

	static void ShowInteractText(SDL_Renderer* r, std::string text, SDL_FRect rect, RGBColor color) {
		auto textLen = text.length();
		auto textOffset = ((textLen / 2.0) * 8);
		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		SDL_RenderDebugText(r, rect.x + (rect.w / 2) - textOffset + 1, rect.y + rect.h + 8 + 1, text.c_str());
		SDL_SetRenderDrawColor(r, 255, 255, 255, color.A);
		SDL_RenderDebugText(r, rect.x + (rect.w / 2) - textOffset, rect.y + rect.h + 8, text.c_str());
	}
};