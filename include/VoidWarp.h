//
// Created by marti on 30/03/2020.
//

#ifndef EXAM_VOIDWARP_H
#define EXAM_VOIDWARP_H


#include "GameObject.h"

class VoidWarp : public GameObject{
public:

    VoidWarp(const char *textureSheet, int w, int h, int x, int y, int id) : GameObject(textureSheet, w, h, x, y, id){}
    void update();
    std::string getType() override;
};


#endif //EXAM_VOIDWARP_H
