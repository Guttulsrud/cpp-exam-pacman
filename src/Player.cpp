//
// Created by mathiss on 3/25/2020.
//

#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/Pellet.h"
#include <iostream>

//enum GameObjectType{WALL, PELLET};

void Player::update() {
    SDL_Rect possiblePosition = m_positionRectangle;

    SDL_Point possibleMovementChange = movementChange;

    if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_W)) {
        possibleMovementChange.x = 0;
        possibleMovementChange.y = -1;
    } else if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_A)) {
        possibleMovementChange.x = -1;
        possibleMovementChange.y = 0;
    } else if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_S)) {
        possibleMovementChange.x = 0;
        possibleMovementChange.y = 1;
    } else if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_D)) {
        possibleMovementChange.x = 1;
        possibleMovementChange.y = 0;
    }

    possiblePosition.x += possibleMovementChange.x;
    possiblePosition.y += possibleMovementChange.y;

    if (positionIsValid(possiblePosition)) {
        m_positionRectangle = possiblePosition;
    }

    else {
        possiblePosition = m_positionRectangle;
        possibleMovementChange = movementChange;

        possiblePosition.x += possibleMovementChange.x;
        possiblePosition.y += possibleMovementChange.y;
        if (positionIsValid(possiblePosition)) {
            m_positionRectangle = possiblePosition;
        }
    }
    movementChange = possibleMovementChange;

}

bool Player::positionIsValid(SDL_Rect &possiblePosition) const {
    bool didNotCollideWithWall = true;
    for (auto &object : Game::getGameObjects()) {
        if (object->getType() == "Wall") {
            if (SDL_HasIntersection(&possiblePosition, &object->m_positionRectangle)) {
                didNotCollideWithWall = false;
            }
        } else if (object->getType() == "Pellet") {
            continue;
            ///Kan fjerne de fra listen, eller gi de en verdi som heter "collected"
            ///Points++
        } else if (object->getType() == "Player") {
            continue;
        }
    }
    return didNotCollideWithWall;
}

std::string Player::getType() {
    return "Player";
}

