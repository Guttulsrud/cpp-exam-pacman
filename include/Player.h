#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H

#include "GameObject.h"
#include "MovableObject.h"

class Player : public MovableObject {
public:
    Player(SDL_Texture * texturePtr, int x, int y, int id, int movementSpeed) : MovableObject(texturePtr, x, y, id, movementSpeed){
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

    void update() override ;
    TYPE getType() override;
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
    SDL_Point movementChange;

    bool positionIsValid(SDL_Rect &possiblePosition);

};


#endif
