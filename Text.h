#pragma once
#ifndef __EMSCRIPTEN__
#include <SDL3_ttf/SDL_ttf.h>
#else
#include <SDL3/SDL.h>
#endif
#include <string>
#include "vector.h"

class Text
{
	bool pendingUpdateTexture = false;

	SDL_Surface* fontSurface = nullptr;
	SDL_Texture* fontTexture = nullptr;
#ifndef __EMSCRIPTEN__
	TTF_Font* font = nullptr;
#endif
	std::string text;
	int point = 24;
	float textScale = 2.0;
	vector2 textSize;
	RGBColor textColor = COLOR_WHITE;
	bool visible = true;
	vector2 overridePosition;

#ifndef __EMSCRIPTEN__
	void GetFont(int);
	void CreateSurface();
#endif
	void CreateTexture(SDL_Renderer*);

public:
	~Text();
	const vector2& GetTextSize() const { return textSize; };
	const SDL_FRect GetBounds(vector2) const;
	void SetText(std::string text, int pt = 24);
	void SetColor(vector3);
	void SetColor(RGBColor);
	void SetOpacity(float);
	void SetVisibility(bool v) { visible = v; };
	void SetPosition(vector2 p) { overridePosition = p; }
	bool IsVisible() { return visible; }
	void Draw(SDL_Renderer*);
	void Draw(SDL_Renderer*, vector2);
};

