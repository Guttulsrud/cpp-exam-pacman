#ifndef EXAM_MOVABLEOBJECT_H
#define EXAM_MOVABLEOBJECT_H


#include "GameObject.h"

class MovableObject : public GameObject {
public:
    MovableObject(SDL_Texture * texturePtr, int w, int h, int x, int y, int id, int movementSpeed) : GameObject(texturePtr, w, h, x, y, id){
        m_movementSpeed = movementSpeed;

    }

protected:
    int m_movementSpeed;
};


#endif
