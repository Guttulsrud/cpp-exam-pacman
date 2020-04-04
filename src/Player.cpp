#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/Pellet.h"
#include "../include/Ghost.h"
#include <iostream>
#include <algorithm>


void Player::update() {
    SDL_Rect possiblePosition = m_positionRectangle;

    SDL_Point possibleMovementChange = movementChange;

    if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_W)) {
        possibleMovementChange.x = 0;
        possibleMovementChange.y = -m_movementSpeed;
        direction = UP;
    } else if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_A)) {
        possibleMovementChange.x = -m_movementSpeed;
        possibleMovementChange.y = 0;
        direction = LEFT;

    } else if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_S)) {
        possibleMovementChange.x = 0;
        possibleMovementChange.y = m_movementSpeed;
        direction = DOWN;
    } else if (!InputManager::getInstance().KeyStillUp(SDL_SCANCODE_D)) {
        possibleMovementChange.x = m_movementSpeed;
        possibleMovementChange.y = 0;
        direction = RIGHT;
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
            if (object->getType() == WALL) {
                didNotCollideWithWall = false;
            } else if (object->getType() == GHOST) {
                std::cout << "OH no, PACMAN be dead" << std::endl;
                //PACMAN IS DEAD
            } else if (object->getType() == PELLET) {
                if (dynamic_cast<Pellet *>(object.get())->m_isPowerPellet) {
                    ///TODO: Trenger bare loope igjennom ghost
                    for (auto &object : Game::getGameObjects()) {
                        if (object->getType() == GHOST) {
                            dynamic_cast<Ghost *>(object.get())->switchedToPowerPelletState = true;
                        }
                    }
                }
                dynamic_cast<Pellet *>(object.get())->eaten = true;
                points++;
            }
        }
    }
    return didNotCollideWithWall;
}

TYPE Player::getType() {
    return PLAYER;
}


void Player::setPlayerAnimationDirectionLarge() {
    switch (direction) {
        case UP:
            texture = largeOpenUp;
            break;
        case DOWN:
            texture = largeOpenDown;
            break;
        case LEFT:
            texture = largeOpenLeft;
            break;
        case RIGHT:
            texture = largeOpenRight;
            break;
    }
}

void Player::setPlayerAnimationDirectionMedium() {
    switch (direction) {
        case UP:
            texture = mediumOpenUp;
            break;
        case DOWN:
            texture = mediumOpenDown;
            break;
        case LEFT:
            texture = mediumOpenLeft;
            break;
        case RIGHT:
            texture = mediumOpenRight;
            break;
    }
}

