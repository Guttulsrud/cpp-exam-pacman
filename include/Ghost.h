#ifndef EXAM_GHOST_H
#define EXAM_GHOST_H

#include "GameObject.h"
#include "MovableObject.h"
#include <map>

class Ghost : public MovableObject {
public:
    Ghost(SDL_Texture *texturePtr, int x, int y, int id, int movementSpeed) : MovableObject(texturePtr, x,
                                                                                            y, id,
                                                                                            movementSpeed) {}

    int difficulty = 4;
    Direction direction = RIGHT;
    std::vector<Direction> prevDirections;
    bool wasAtIntersection = false;
    bool powerPelletState = false;
    bool switchedToPowerPelletState = false;

    void update() override;

    TYPE getType() override;

    Direction getDirectionToPlayer(const std::map<Direction, SDL_Rect> &possibleDirections) const;

};

#endif //EXAM_GHOST_H
