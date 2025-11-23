#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "vector.h"

class Text
{
	bool pendingUpdateTexture = false;

	SDL_Surface* fontSurface = nullptr;
	SDL_Texture* fontTexture = nullptr;
	TTF_Font* font = nullptr;
	std::string text;
	int point = 24;
	vector2 textSize;
	RGBColor textColor = COLOR_WHITE;

	void GetFont(int);
	void CreateSurface();
	void CreateTexture(SDL_Renderer*);

public:
	~Text();
	const vector2& GetTextSize() const { return textSize; };
	const SDL_FRect GetBounds(vector2) const;
	void SetText(std::string text, int pt = 24);
	void SetColor(vector3);
	void SetColor(RGBColor);
	void SetOpacity(float);
	void Draw(SDL_Renderer*, vector2);
};

