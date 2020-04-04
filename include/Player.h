#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H

#include "GameObject.h"
#include "TextureManager.h"
#include "Ghost.h"

class Player : public GameObject {
public:
    Player(SDL_Texture * texturePtr, int w, int h, int x, int y, int id, int movementSpeed) : GameObject(texturePtr, w, h, x, y, id){
        m_movementSpeed = movementSpeed;
        base = TextureManager::loadTexture("../resources/img/pacman/base.png");
        mediumOpenRight = TextureManager::loadTexture("../resources/img/pacman/medium-open-right.png");
        mediumOpenLeft = TextureManager::loadTexture("../resources/img/pacman/medium-open-left.png");
        mediumOpenUp = TextureManager::loadTexture("../resources/img/pacman/medium-open-up.png");
        mediumOpenDown = TextureManager::loadTexture("../resources/img/pacman/medium-open-down.png");
        largeOpenRight = TextureManager::loadTexture("../resources/img/pacman/large-open-right.png");
        largeOpenLeft = TextureManager::loadTexture("../resources/img/pacman/large-open-left.png");
        largeOpenUp = TextureManager::loadTexture("../resources/img/pacman/large-open-up.png");
        largeOpenDown = TextureManager::loadTexture("../resources/img/pacman/large-open-down.png");
    }

    void update() override;
    std::string getType() override;
    Direction direction;

    SDL_Texture * base;
    SDL_Texture * mediumOpenRight;
    SDL_Texture * mediumOpenLeft;
    SDL_Texture * mediumOpenUp;
    SDL_Texture * mediumOpenDown;
    SDL_Texture * largeOpenRight;
    SDL_Texture * largeOpenLeft;
    SDL_Texture * largeOpenUp;
    SDL_Texture * largeOpenDown;
    int points;


    void setPlayerAnimationDirectionLarge();
    void setPlayerAnimationDirectionMedium();

private:
    int m_movementSpeed;
    SDL_Point movementChange;

    bool positionIsValid(SDL_Rect &possiblePosition);

};


#endif
