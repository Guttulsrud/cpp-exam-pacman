//
// Created by mathi on 4/5/2020.
//

#ifndef EXAM_STATIONARYOBJECT_H
#define EXAM_STATIONARYOBJECT_H


#include "GameObject.h"

class StationaryObject : public GameObject{

public:
    StationaryObject( TYPE t, int id, int x, int y, SDL_Texture * texturePtr, int h = 30, int w = 30) : GameObject(w, h, x, y, id, texturePtr){

        m_type = t;
    }
    TYPE getType() override;
    TYPE m_type;
};


#endif //EXAM_STATIONARYOBJECT_H
