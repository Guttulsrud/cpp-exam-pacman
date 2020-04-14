#ifndef EXAM_TEXTUREMANAGER_H
#define EXAM_TEXTUREMANAGER_H


#include <SDL2/SDL.h>
#include <string>

class TextureManager {
public:
    static SDL_Texture *loadTexture(const std::string& path);
};

#endif
