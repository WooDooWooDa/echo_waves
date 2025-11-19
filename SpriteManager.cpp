#include "SpriteManager.h"
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_filesystem.h>
#include <iostream>

void SpriteManager::LoadTexture(SDL_Renderer* renderer, std::string spriteName)
{
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = new SDL_Texture();

    std::string png_path;
#ifdef __EMSCRIPTEN__
    png_path = baseSpritePath + spriteName + ".bmp";
#else
    png_path = "./assets/sprites/" + spriteName + ".bmp"; // Desktop path
#endif
    
    surface = SDL_LoadBMP(png_path.c_str());//IMG_Load(png_path.c_str());
    if (!surface) {
        std::cout << "Error loading bitmap image : " << SDL_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    if (!texture) {
        std::cout << "Error creating texture from surface for : " << spriteName << std::endl;
        return;
    }
    loaded_textures.insert({ spriteName, texture });
}

SpriteManager::~SpriteManager()
{
    for (auto& texture : loaded_textures) {
        SDL_DestroyTexture(texture.second);
    }
    loaded_textures.clear();
}

SDL_Texture* SpriteManager::GetTexture(std::string img)
{
    if (!isInit) {
        std::cout << "Sprite Manager not yet initialized" << std::endl;
        return nullptr;
    }

    auto tex = loaded_textures.find(img);
    if (tex != loaded_textures.end())
        return tex->second;

    std::cout << "No texture found for : " + img << std::endl;
    return nullptr;
}

void SpriteManager::LoadAllTextures(SDL_Renderer* renderer)
{
    if (isInit) return;

    LoadTexture(renderer, "clap");
    LoadTexture(renderer, "close_door");
    LoadTexture(renderer, "open_door");
    LoadTexture(renderer, "key");
    LoadTexture(renderer, "wall");
    LoadTexture(renderer, "broken_wall");
    LoadTexture(renderer, "xylophone");
    LoadTexture(renderer, "gong");
    LoadTexture(renderer, "piano_0");
    LoadTexture(renderer, "piano_1");
    LoadTexture(renderer, "piano_2");
    LoadTexture(renderer, "piano_3");
    LoadTexture(renderer, "piano_4");
    LoadTexture(renderer, "tuba");

    isInit = true;
}
