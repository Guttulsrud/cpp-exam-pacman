//
// Created by mathi on 3/25/2020.
//

#ifndef EXAM_WALLENTITY_H
#define EXAM_WALLENTITY_H


#include <iostream>
#include "GameObject.h"

class WallEntity : public GameObject {

public:
    WallEntity(const char *textureSheet, int w, int h, int x, int y, int id) : GameObject(textureSheet, w, h, x, y, id){
        std::cout << "I AM CREATE" << std::endl;
    }
    void update() override;

};


#endif //EXAM_WALLENTITY_H
