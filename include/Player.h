#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H

#include "GameObject.h"
#include "MovableObject.h"
#include "EntityAnimator.h"

class Player : public MovableObject {
public:
    Player(SDL_Texture *texturePtr, int x, int y, int id, int movementSpeed, EntityAnimator animator) :
            MovableObject(texturePtr, x, y, id, movementSpeed), m_animator(animator) {
    }

    void update() override;
    TYPE getType() override;
    Direction direction = UP;
    EntityAnimator m_animator;
    int points;

private:
    SDL_Point movementChange;

    bool positionIsValid(SDL_Rect &possiblePosition);

    void determineDirection(const SDL_Rect &possiblePosition);
};


#endif
