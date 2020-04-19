#ifndef EXAM_PELLET_H
#define EXAM_PELLET_H

#include "GameObject.h"
#include "Stationary.h"

class Pellet : public Stationary {
public:
    Pellet(SDL_Texture *texturePtr, int x, int y, int w, int h, bool isPowerPellet = false, bool isFruit = false) :
            Stationary(TYPE::PELLET, x, y, texturePtr, h, w),
            m_isPowerPellet(isPowerPellet),
            m_isFruit(isFruit) {}

    bool m_eaten = false;
    bool m_isPowerPellet;
    bool m_isFruit;
private:

};


#endif