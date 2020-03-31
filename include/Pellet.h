#ifndef EXAM_PELLET_H
#define EXAM_PELLET_H


#include "GameObject.h"

class Pellet {
public:
    Pellet(SDL_Texture * tex, SDL_Rect rect, bool collided){
        rectangle = rect;
        texture = tex;
        collided = false;
    }

    SDL_Rect rectangle;
    SDL_Texture * texture;
    bool collided;
};


#endif