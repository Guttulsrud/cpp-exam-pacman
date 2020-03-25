//
// Created by mathi on 3/25/2020.
//

#include "Player.h"
#include "InputManager.h"

void Player::update() {

    if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_W)) {
        m_positionRectangle.y -= m_movementSpeed;
        direction = UP;
    }
    else if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_A)) {
        m_positionRectangle.x -= m_movementSpeed;
        direction = LEFT;
    }
    else if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_S)) {
        m_positionRectangle.y += m_movementSpeed;
        direction = DOWN;
    }
    else if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_D)) {
        m_positionRectangle.x += m_movementSpeed;
        direction = RIGHT;
    } else {
        switch(direction){
            case UP:
                m_positionRectangle.y -= m_movementSpeed;
                break;
            case DOWN:
                m_positionRectangle.y += m_movementSpeed;
                break;
            case RIGHT:
                m_positionRectangle.x += m_movementSpeed;
                break;
            case LEFT:
                m_positionRectangle.x -= m_movementSpeed;
                break;
        }
    }
}
