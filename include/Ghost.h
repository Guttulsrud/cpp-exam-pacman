//
// Created by mathi on 3/31/2020.
//

#ifndef EXAM_GHOST_H
#define EXAM_GHOST_H


#include <map>
#include <experimental/vector>
#include "GameObject.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Ghost : public GameObject {
public:
    Ghost(SDL_Texture *texturePtr, int w, int h, int x, int y, int id, int movementSpeed) : GameObject(texturePtr, w, h,
                                                                                                       x, y, id) {
        m_movementSpeed = movementSpeed;
    }

    int m_movementSpeed;

    Direction direction = RIGHT;
    std::vector<Direction> prevDirections;
    bool wasAtIntersection = false;

    void update() override;

    std::string getType() override;
};


#endif //EXAM_GHOST_H
