#include "FontManager.h"

void FontManager::LoadFont()
{
	auto path = GetFontPath("echo.ttf");
	fonts.insert({ 24, TTF_OpenFont(path.c_str(), 24)});
	fonts.insert({ 36, TTF_OpenFont(path.c_str(), 36) });
	fonts.insert({ 48, TTF_OpenFont(path.c_str(), 48) });
	fonts.insert({ 60, TTF_OpenFont(path.c_str(), 60) });
	fonts.insert({ 72, TTF_OpenFont(path.c_str(), 72) });
}

TTF_Font* FontManager::GetFont(int pointSize)
{
	auto found = fonts.find(pointSize);
	if (found != fonts.end()) {
		return found->second;
	}
	return nullptr;
}
