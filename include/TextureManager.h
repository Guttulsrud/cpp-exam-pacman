//
// Created by Halo_ on 25.03.2020.
//

#ifndef EXAM_TEXTUREMANAGER_H
#define EXAM_TEXTUREMANAGER_H


#include "SDL.h"

class TextureManager {
public:
    static SDL_Texture *loadTexture(const char *fileName);
    static void draw(SDL_Texture*, SDL_Rect src, SDL_Rect dest);

};



#endif //EXAM_TEXTUREMANAGER_H
