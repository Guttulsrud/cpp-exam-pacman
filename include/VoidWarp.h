#ifndef EXAM_VOIDWARP_H
#define EXAM_VOIDWARP_H

#include "GameObject.h"
#include "MovableObject.h"
#include "StationaryObject.h"

class VoidWarp : public StationaryObject{
public:

    int m_side = 0;
    VoidWarp(SDL_Texture * texturePtr, int w, int h, int x, int y, int id, int side) : StationaryObject(VOIDWARP, id, x, y, texturePtr, h, w){
        m_side = side;
    }

    void update();
    TYPE getType() override;
};


#endif
