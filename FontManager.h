#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

class FontManager
{
private:
	static std::string GetFontPath(const std::string& fontPath)
	{
#ifdef __EMSCRIPTEN__
		return "/assets/font/" + fontPath;
#else
		return "./assets/font/" + fontPath;
#endif
	}

	inline static bool isInit;

	inline static std::unordered_map<int, TTF_Font*> fonts;

public:
	void LoadFont();

	static TTF_Font* GetFont(int);

	bool IsInit() { return isInit; }
};

