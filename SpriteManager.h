#pragma once
#include <string>
#include <SDL3/SDL_render.h>
#include <unordered_map>

class SpriteManager
{
private:
	inline static bool isInit;
	inline static std::unordered_map<std::string, SDL_Texture*> loaded_textures;

	std::string baseSpritePath = "/assets/sprites/";

	void LoadTexture(SDL_Renderer* , std::string);

public:
	~SpriteManager();
	static SDL_Texture* GetTexture(std::string);
	void LoadAllTextures(SDL_Renderer*);

	bool IsInit() { return isInit; }
};

