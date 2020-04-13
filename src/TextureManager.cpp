#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "../include/TextureManager.h"
#include "../include/GameManager.h"

SDL_Texture *TextureManager::loadTexture(const char *texture) {
    SDL_Surface *surface = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(GameManager::renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}
