#ifndef EXAM_TEXTUREMANAGER_H
#define EXAM_TEXTUREMANAGER_H


#include <SDL2/SDL.h>

class TextureManager {
public:
    static SDL_Texture *loadTexture(const char *fileName);
};

#endif
