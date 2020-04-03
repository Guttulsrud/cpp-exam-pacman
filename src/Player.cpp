#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/Pellet.h"
#include <iostream>
#include <algorithm>


void Player::update() {
    SDL_Rect possiblePosition = m_positionRectangle;

    SDL_Point possibleMovementChange = movementChange;

    if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_W)) {
        possibleMovementChange.x = 0;
        possibleMovementChange.y = -m_movementSpeed;
    } else if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_A)) {
        possibleMovementChange.x = -m_movementSpeed;
        possibleMovementChange.y = 0;
    } else if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_S)) {
        possibleMovementChange.x = 0;
        possibleMovementChange.y = m_movementSpeed;
    } else if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_D)) {
        possibleMovementChange.x = m_movementSpeed;
        possibleMovementChange.y = 0;
    }

    possiblePosition.x += possibleMovementChange.x;
    possiblePosition.y += possibleMovementChange.y;

    if (positionIsValid(possiblePosition)) {
        m_positionRectangle = possiblePosition;
    } else {
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

bool Player::positionIsValid(SDL_Rect &possiblePosition) {
    bool didNotCollideWithWall = true;


    for (auto &object : Game::getGameObjects()) {

        if (SDL_HasIntersection(&possiblePosition, &object->m_positionRectangle)) {
            if (object->getType() == "Wall") {
                didNotCollideWithWall = false;
            } else if (object->getType() == "Pellet") {
                dynamic_cast<Pellet *>(object.get())->eaten = true;


                points++;
            }
        }
    }
    return didNotCollideWithWall;
}

std::string Player::getType() {
    return "Player";
}

