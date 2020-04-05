//
// Created by mathi on 4/5/2020.
//

#ifndef EXAM_STATIONARYOBJECT_H
#define EXAM_STATIONARYOBJECT_H


#include "GameObject.h"

class StationaryObject : public GameObject{
    TYPE getType() override;
    TYPE m_type;
public:
    StationaryObject(SDL_Texture * texturePtr, int x, int y, int id, TYPE t) : GameObject(30, 30, x, y, id, texturePtr){
        m_type = t;
    }
};


#endif //EXAM_STATIONARYOBJECT_H
