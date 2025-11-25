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

	static constexpr int FONT_SIZE_24 = 24;
	static constexpr int FONT_SIZE_36 = 36;
	static constexpr int FONT_SIZE_48 = 48;
	static constexpr int FONT_SIZE_60 = 60;
	static constexpr int FONT_SIZE_72 = 72;

	void LoadFont();

	static TTF_Font* GetFont(int);

	bool IsInit() { return isInit; }
};

