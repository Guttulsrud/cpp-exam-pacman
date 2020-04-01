//
// Created by mathi on 3/25/2020.
//

#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H


#include "GameObject.h"

class Player : public GameObject {
public:
    Player(SDL_Texture * texturePtr, int w, int h, int x, int y, int id, int movementSpeed) : GameObject(texturePtr, w, h, x, y, id){
        m_movementSpeed = movementSpeed;
    }

    void update() override;
    std::string getType() override;

private:
    int m_movementSpeed;
    SDL_Point movementChange;

    bool positionIsValid(SDL_Rect &possiblePosition) const;
};


#endif //EXAM_PLAYER_H
