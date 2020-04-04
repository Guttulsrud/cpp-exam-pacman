//
// Created by mathi on 4/3/2020.
//

#ifndef EXAM_HALLWAY_H
#define EXAM_HALLWAY_H


#include "GameObject.h"

class Hallway : public GameObject {

    void update() override;

    TYPE getType() override;

public:
    Hallway(SDL_Texture * texturePtr, int w, int h, int x, int y, int id) : GameObject(texturePtr, w, h, x, y, id){}
};


#endif //EXAM_HALLWAY_H
