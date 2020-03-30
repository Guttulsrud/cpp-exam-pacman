//
// Created by marti on 30/03/2020.
//

#ifndef EXAM_VOIDWARP_H
#define EXAM_VOIDWARP_H


#include "GameObject.h"

class VoidWarp : public GameObject{
public:

    int m_side = 0;
    VoidWarp(const char *textureSheet, int w, int h, int x, int y, int id, int side) : GameObject(textureSheet, w, h, x, y, id){
        m_side = side;
    }
    void update();
    std::string getType() override;
};


#endif //EXAM_VOIDWARP_H
