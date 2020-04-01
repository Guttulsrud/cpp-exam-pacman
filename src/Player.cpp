//
// Created by mathiss on 3/25/2020.
//

#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Map.h"
#include <iostream>

void Player::update() {
    SDL_Rect desiredPosition = m_positionRectangle;

    if (InputManager::getInstance().KeyDown(SDL_SCANCODE_W)) {
        movementChangeY = -m_movementSpeed;
    } else if (InputManager::getInstance().KeyDown(SDL_SCANCODE_A)) {
        movementChangeX = -m_movementSpeed;
    } else if (InputManager::getInstance().KeyDown(SDL_SCANCODE_S)) {
        movementChangeY = m_movementSpeed;
    } else if (InputManager::getInstance().KeyDown(SDL_SCANCODE_D)) {
        movementChangeX = m_movementSpeed;
    }
    desiredPosition.x += movementChangeX;
    desiredPosition.y += movementChangeY;

    bool collidedWithWall = false;
    for (auto &wall : Map::walls) {
        if (SDL_HasIntersection(&desiredPosition, &wall)) {
            collidedWithWall = true;
        }
    }

    if(!collidedWithWall){
        m_positionRectangle = desiredPosition;
    }



}

std::string Player::getType() {
    return "Player";
}

