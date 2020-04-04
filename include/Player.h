#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H

#include "GameObject.h"
#include "TextureManager.h"
#include "Ghost.h"

class Player : public GameObject {
public:
    Player(SDL_Texture * texturePtr, int w, int h, int x, int y, int id, int movementSpeed) : GameObject(texturePtr, w, h, x, y, id){
        m_movementSpeed = movementSpeed;
        playerClosed = TextureManager::loadTexture("../resources/img/pacman-open-left.png");
    }

    void update() override;
    std::string getType() override;
    Direction direction;
    SDL_Texture * playerClosed;
    int points;

private:
    int m_movementSpeed;
    SDL_Point movementChange;

    bool positionIsValid(SDL_Rect &possiblePosition);
};


#endif
