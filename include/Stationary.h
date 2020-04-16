#ifndef EXAM_STATIONARY_H
#define EXAM_STATIONARY_H


#include "GameObject.h"

class Stationary : public GameObject{

public:
    Stationary(TYPE t, int x, int y, SDL_Texture * texturePtr, int h = 30, int w = 30) : GameObject(w, h, x, y, texturePtr){

        m_type = t;
    }
    TYPE getType() override;
    TYPE m_type;
};


#endif
