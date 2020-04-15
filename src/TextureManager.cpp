#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "../include/TextureManager.h"
#include "../include/GameManager.h"



std::map<std::string, SDL_Texture *> TextureManager::createdTextures;

SDL_Texture *TextureManager::loadTexture(const std::string& path) {
    const char * imagePath = path.c_str();
    if(!createdTextures.count(imagePath)){
        SDL_Surface *surface = IMG_Load(imagePath);
        createdTextures[imagePath] = SDL_CreateTextureFromSurface(SDLManager::m_renderer, surface);
        SDL_FreeSurface(surface);
    }
    return createdTextures[imagePath];
}

