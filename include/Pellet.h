#ifndef EXAM_PELLET_H
#define EXAM_PELLET_H

#include "GameObject.h"
#include "Stationary.h"

class Pellet : public Stationary{
public:
    Pellet(SDL_Texture *texturePtr, int x, int y, int id, int w, int h, bool isPowerPellet = false) : Stationary(PELLET, id, x, y, texturePtr, h, w){
        m_isPowerPellet = isPowerPellet;
    }
    void update();
    TYPE getType() override;

    bool eaten = false;
    bool m_isPowerPellet;
};


#endif