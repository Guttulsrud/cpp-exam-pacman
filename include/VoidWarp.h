#ifndef EXAM_VOIDWARP_H
#define EXAM_VOIDWARP_H

#include "GameObject.h"
#include "MovableObject.h"

class VoidWarp : public MovableObject{
public:

    int m_side = 0;
    VoidWarp(SDL_Texture * texturePtr, int w, int h, int x, int y, int id, int side) : MovableObject(texturePtr, x, y, id, 0){
        m_side = side;
    }

    void update();
    TYPE getType() override;
};


#endif
