#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "../include/TextureManager.h"
#include "../include/Game.h"

SDL_Texture *TextureManager::loadTexture(const char *texture) {
    SDL_Surface *surface = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    return tex;
}

void TextureManager::draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
