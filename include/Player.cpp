//
// Created by mathi on 3/25/2020.
//

#include "Player.h"
#include "InputManager.h"

void Player::update() {

    if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_W)) {
        m_positionRectangle.y -= m_movementSpeed;
    }
    else if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_A)) {
        m_positionRectangle.x -= m_movementSpeed;
    }
    else if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_S)) {
        m_positionRectangle.y += m_movementSpeed;
    }
    else if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_D)) {
        m_positionRectangle.x += m_movementSpeed;
    }

}
