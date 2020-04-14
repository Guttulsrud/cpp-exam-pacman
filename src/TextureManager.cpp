#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "../include/TextureManager.h"
#include "../include/GameManager.h"

SDL_Texture *TextureManager::loadTexture(const std::string& path) {
    const char * texture = path.c_str();
    SDL_Surface *surface = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(GameManager::renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}
