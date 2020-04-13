#ifndef EXAM_MOVABLEOBJECT_H
#define EXAM_MOVABLEOBJECT_H


#include "GameObject.h"

class MovableObject : public GameObject {
public:
    MovableObject(SDL_Texture * texturePtr, int x, int y, int id, int movementSpeed) : GameObject(60, 60, x, y, id, texturePtr){
        m_movementSpeed = movementSpeed;
        hitbox.h = 20;
        hitbox.w = 20;
        hitbox.x = x;
        hitbox.y = y;
    }
    SDL_Rect hitbox;
    void updateHitbox();
    virtual void update() = 0;
    virtual void reset() = 0;
    int framesSinceTextureChange = 0;
protected:
    int m_movementSpeed;
};


#endif
