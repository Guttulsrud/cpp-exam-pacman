#ifndef EXAM_MOVABLEOBJECT_H
#define EXAM_MOVABLEOBJECT_H


#include "GameObject.h"

class MovableObject : public GameObject {
public:
    MovableObject(SDL_Texture * texturePtr, int x, int y, int id, int movementSpeed) : GameObject(60, 60, x, y, id, texturePtr){
        m_movementSpeed = movementSpeed;
        m_texture = texturePtr;
    }
    SDL_Texture * m_texture;
    virtual void update() = 0;
    int framesSinceTextureChange = 0;
protected:
    int m_movementSpeed;
};


#endif
