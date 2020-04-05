#ifndef EXAM_PELLET_H
#define EXAM_PELLET_H

#include "GameObject.h"
#include "StationaryObject.h"

class Pellet : public StationaryObject{
public:
    Pellet(SDL_Texture *texturePtr, int x, int y, int id, int w, int h, bool isPowerPellet = false) : StationaryObject(PELLET, id, x, y, texturePtr, h, w){
        m_isPowerPellet = isPowerPellet;
    }
    void update();
    TYPE getType() override;

    bool eaten = false;
    bool m_isPowerPellet;
};


#endif