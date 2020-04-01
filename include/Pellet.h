#ifndef EXAM_PELLET_H
#define EXAM_PELLET_H


#include "GameObject.h"

class Pellet : public GameObject{
public:
    Pellet(const char *textureSheet, int w, int h, int x, int y, int id) : GameObject(textureSheet, w, h, x, y, id){}
    void update() override;
    std::string getType() override;
};


#endif