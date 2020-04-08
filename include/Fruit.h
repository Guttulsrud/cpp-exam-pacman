//
// Created by marti on 08/04/2020.
//

#ifndef EXAM_FRUIT_H
#define EXAM_FRUIT_H


#include "StationaryObject.h"

class Fruit : public StationaryObject {
public:
    Fruit(SDL_Texture *texturePtr, int x, int y, int id, int w, int h, bool active) : StationaryObject(FRUIT, id, x, y, texturePtr, h, w){
    }

    void update();
    TYPE getType() override;

    bool eaten = false;
    bool m_active = false;
};


#endif //EXAM_FRUIT_H
