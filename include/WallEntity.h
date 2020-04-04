#ifndef EXAM_WALLENTITY_H
#define EXAM_WALLENTITY_H

#include "GameObject.h"

class WallEntity : public GameObject {

public:
    WallEntity(SDL_Texture * texturePtr, int w, int h, int x, int y, int id) : GameObject(texturePtr, w, h, x, y, id){}
    void update() override;
    TYPE getType() override ;

};


#endif
