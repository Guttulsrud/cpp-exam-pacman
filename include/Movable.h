#ifndef EXAM_MOVABLE_H
#define EXAM_MOVABLE_H

#include "GameObject.h"

class Movable : public GameObject {
public:
    Movable(int x, int y, int movementSpeed) : GameObject(60, 60, x, y){
        m_movementSpeed = movementSpeed;
        m_hitBox.h = 20;
        m_hitBox.w = 20;
        m_hitBox.x = x;
        m_hitBox.y = y;
    }
    void moveInBoundsIfOutOfBounds();
    void updateHitBox();
    virtual void update() = 0;
    virtual void reset() = 0;
    bool willCollideWithWall(SDL_Rect &possiblePosition);
    int m_movementSpeed;
    SDL_Rect m_hitBox;
};


#endif
