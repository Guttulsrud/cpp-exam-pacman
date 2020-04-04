#ifndef EXAM_PELLET_H
#define EXAM_PELLET_H

#include "GameObject.h"

class Pellet : public GameObject{
public:
    Pellet(SDL_Texture *texturePtr, int w, int h, int x, int y, int id, bool isPowerPellet = false) : GameObject(texturePtr, w, h, x, y, id){
        m_isPowerPellet = isPowerPellet;
    }
    void update() override;
    TYPE getType() override;

    bool eaten = false;
    bool m_isPowerPellet;

};


#endif