#ifndef EXAM_MOVABLE_H
#define EXAM_MOVABLE_H


#include "GameObject.h"

class Movable : public GameObject {
public:
    Movable(SDL_Texture * texturePtr, int x, int y, int movementSpeed) : GameObject(60, 60, x, y, texturePtr){
        m_movementSpeed = movementSpeed;
        hitBox.h = 20;
        hitBox.w = 20;
        hitBox.x = x;
        hitBox.y = y;
    }
    SDL_Rect hitBox;
    void moveInBoundsIfOutOfBounds();
    void updateHitBox();
    virtual void update() = 0;
    virtual void reset() = 0;
    int framesSinceTextureChange = 0;
    int m_movementSpeed;
};


#endif
