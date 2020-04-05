#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/Pellet.h"
#include "../include/Ghost.h"
#include <iostream>
#include <algorithm>


void Player::update() {
    framesSinceTextureChange++;
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


    // Check for collision with moving game objects
    for (auto &movable : Game::getMovableGameObjects()) {
        if (SDL_HasIntersection(&possiblePosition, &movable->m_positionRectangle) && movable->getType() == GHOST) {
            std::cout << "OH no, PACMAN be dead" << std::endl;

        }
    }


    // Check for collision with stationary game objects
    for (auto &stationary : Game::getStationaryGameObjects()) {

        if (SDL_HasIntersection(&possiblePosition, &stationary->m_positionRectangle)) {
            if (stationary->getType() == WALL) {
                didNotCollideWithWall = false;
            }

            if (stationary->getType() == PELLET) {
                if (dynamic_cast<Pellet *>(stationary.get())->m_isPowerPellet) {
                    //TODO: Trenger bare loope igjennom ghost

                    //TODO:  Denne bør være en egen funksjon, eventuelt bruke loopen over og sjekke power state et annet sted?
                    for (auto &o : Game::getMovableGameObjects()) {
                        if (o->getType() == GHOST) {
                            dynamic_cast<Ghost *>(o.get())->switchedToPowerPelletState = true;
                        }
                    }
                }
                dynamic_cast<Pellet *>(stationary.get())->eaten = true;
                points++;
            }
        }
    }
    return didNotCollideWithWall;
}

TYPE Player::getType() {
    return PLAYER;
}

void Player::handleAnimations() {

}
