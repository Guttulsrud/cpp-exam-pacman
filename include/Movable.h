#ifndef EXAM_MOVABLE_H
#define EXAM_MOVABLE_H


#include "GameObject.h"

class Movable : public GameObject {
public:
    Movable(SDL_Texture * texturePtr, int w, int h, int x, int y, int id, int movementSpeed) : GameObject(texturePtr, w, h, x, y, id){
        m_movementSpeed = movementSpeed;

    }

protected:
    int m_movementSpeed;
};


#endif
