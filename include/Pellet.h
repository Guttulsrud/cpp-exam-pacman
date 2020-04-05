#ifndef EXAM_PELLET_H
#define EXAM_PELLET_H

#include "GameObject.h"

class Pellet : public GameObject{
public:
    Pellet(SDL_Texture *texturePtr, int x, int y, int id, bool isPowerPellet = false) : GameObject(5,5, x, y, id, texturePtr){
        m_isPowerPellet = isPowerPellet;
    }
    void update();
    TYPE getType() override;

    bool eaten = false;
    bool m_isPowerPellet;
};


#endif