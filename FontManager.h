#pragma once
#ifndef __EMSCRIPTEN__
#include <SDL3_ttf/SDL_ttf.h>
#endif
#include <string>
#include <unordered_map>

class FontManager
{
private:
	static std::string GetFontPath(const std::string& fontPath)
	{
		return "./assets/font/" + fontPath;
	}

	inline static bool isInit;

#ifndef __EMSCRIPTEN__
	inline static std::unordered_map<int, TTF_Font*> fonts;
#endif

public:

	static constexpr int FONT_SIZE_24 = 24;
	static constexpr int FONT_SIZE_36 = 36;
	static constexpr int FONT_SIZE_48 = 48;
	static constexpr int FONT_SIZE_60 = 60;
	static constexpr int FONT_SIZE_72 = 72;

#ifndef __EMSCRIPTEN__
	void LoadFont();

	static TTF_Font* GetFont(int);
#endif

	bool IsInit() { return isInit; }
};
