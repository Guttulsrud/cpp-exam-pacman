//
// Created by mathi on 3/25/2020.
//

#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H


#include "GameObject.h"

enum DIRECTION{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class Player : public GameObject {
public:
    Player(const char *textureSheet, int w, int h, int x, int y, int id, int movementSpeed) : GameObject(textureSheet, w, h, x, y, id){
        m_movementSpeed = movementSpeed;
    }

    void update() override;

private:
    DIRECTION direction;
    int m_movementSpeed;
};


#endif //EXAM_PLAYER_H
