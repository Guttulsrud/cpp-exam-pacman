#ifndef EXAM_FRUIT_H
#define EXAM_FRUIT_H


#include "Stationary.h"

class Fruit : public Stationary {
public:
    Fruit(SDL_Texture *texturePtr, int x, int y, int id, int w, int h, bool active) : Stationary(FRUIT, id, x, y, texturePtr, h, w){
    }

    void update();
    TYPE getType() override;
    bool eaten = false;
    bool m_active = false;

    Uint32 fruitSpawnCallback(Uint32 n, void *fruit);
};


#endif
