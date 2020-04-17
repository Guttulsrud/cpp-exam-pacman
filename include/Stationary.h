#ifndef EXAM_STATIONARY_H
#define EXAM_STATIONARY_H


#include "GameObject.h"

class Stationary : public GameObject {

public:
    Stationary(TYPE t, int x, int y, SDL_Texture *texturePtr, int h = 30, int w = 30)
            : GameObject(w, h, x, y),
              m_type(t) {
        m_texture = texturePtr;
    }

    TYPE getType() {
        return m_type;
    }

private:
    TYPE m_type;
};


#endif
