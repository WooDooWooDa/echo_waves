#include "Text.h"
#include "FontManager.h"

#ifndef __EMSCRIPTEN__
void Text::GetFont(int pt)
{
	auto newfont = FontManager::GetFont(pt);
	if (newfont == nullptr) return;

	font = newfont;
}

void Text::CreateSurface()
{
	SDL_Color color = {(Uint8)textColor.R, (Uint8)textColor.G, 
		(Uint8)textColor.B, (Uint8)textColor.A};
	fontSurface = TTF_RenderText_Blended(font, text.c_str(), text.length(), color);
}
#endif

void Text::CreateTexture(SDL_Renderer* renderer)
{
#ifndef __EMSCRIPTEN__
	if (font == nullptr) return;

	CreateSurface();
	fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	if (!fontTexture) return;

	float textWidth, textHeight;
	SDL_GetTextureSize(fontTexture, &textWidth, &textHeight);

	textSize = vector2(textWidth, textHeight);
#else
	textSize = vector2(text.length() * 8 * textScale, 8 * textScale);
#endif

	pendingUpdateTexture = false;
}

Text::~Text()
{
	SDL_DestroySurface(fontSurface);
	SDL_DestroyTexture(fontTexture);
}

const SDL_FRect Text::GetBounds(vector2 position) const
{
	SDL_FRect rect{};
	rect.x = position.X - textSize.X / 2;
	rect.y = position.Y - textSize.Y / 2;
	rect.w = textSize.X;
	rect.h = textSize.Y;
	return rect;
}

void Text::SetText(std::string newText, int pt)
{
	text = newText;

#ifndef __EMSCRIPTEN__
	if (point != pt || font == nullptr) {
		GetFont(pt);
		point = pt;
	}
#endif

	pendingUpdateTexture = true;
}

void Text::SetColor(vector3 newColor)
{
	SetColor(RGBColor{newColor.X, newColor.Y, newColor.Z, 255});
}

void Text::SetColor(RGBColor newColor)
{
	textColor = newColor;
}

void Text::SetOpacity(float opacity)
{
	if (opacity < 0) opacity = 0;
	if (opacity > 255) opacity = 255;
	textColor.A = opacity;
}

void Text::Draw(SDL_Renderer* r)
{
	Text::Draw(r, overridePosition);
}

void Text::Draw(SDL_Renderer* renderer, vector2 position)
{
	if (!visible || text.empty()) return;

	if (pendingUpdateTexture || fontTexture == nullptr)
		CreateTexture(renderer);

	auto& rect = GetBounds(position);
#ifndef __EMSCRIPTEN__
	SDL_RenderTexture(renderer, fontTexture, NULL, &rect);
#else
	SDL_SetRenderScale(renderer, textScale, textScale);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, textColor.A);
	SDL_RenderDebugText(renderer, rect.x / textScale, rect.y / textScale, text.c_str());
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
#endif
}
