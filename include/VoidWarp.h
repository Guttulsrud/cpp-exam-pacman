//
// Created by marti on 30/03/2020.
//

#ifndef EXAM_VOIDWARP_H
#define EXAM_VOIDWARP_H


#include "GameObject.h"

class VoidWarp : public GameObject{
public:

    int m_side = 0;
    VoidWarp(SDL_Texture * texturePtr, int w, int h, int x, int y, int id, int side) : GameObject(texturePtr, w, h, x, y, id){
        m_side = side;
    }

    void update() override ;
    std::string getType() override;
};


#endif //EXAM_VOIDWARP_H
