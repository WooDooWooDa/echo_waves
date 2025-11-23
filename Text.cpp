#include "Text.h"
#include "FontManager.h"

void Text::GetFont(int pt)
{
	auto newfont = FontManager::GetFont(pt);
	if (newfont == nullptr) return;

	font = newfont;
	CreateSurface();
}

void Text::CreateSurface()
{
	SDL_Color color = {textColor.R, textColor.G, textColor.B, textColor.A};
	fontSurface = TTF_RenderText_Blended(font, text.c_str(), text.length(), color);
}

void Text::CreateTexture(SDL_Renderer* renderer)
{
	if (font == nullptr || !fontSurface) return;

	fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	if (!fontTexture) return;

	float textWidth, textHeight;
	SDL_GetTextureSize(fontTexture, &textWidth, &textHeight);

	textSize = vector2(textWidth, textHeight);

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
	if (point != pt || font == nullptr) {
		GetFont(pt);
		point = pt;
	}

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

void Text::Draw(SDL_Renderer* renderer, vector2 position)
{
	if (text.empty()) return;

	if (pendingUpdateTexture || fontTexture == nullptr)
		CreateTexture(renderer);

	auto& rect = GetBounds(position);
	SDL_RenderTexture(renderer, fontTexture, NULL, &rect);
}
