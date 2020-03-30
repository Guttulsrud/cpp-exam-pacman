//
// Created by mathiss on 3/25/2020.
//

#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/Map.h"
#include "../include/TextureManager.h"
#include <iostream>

void Player::update() {

    //TODO: possible to clip through walls by holding 90 degree of movement button

    SDL_Rect desiredPosition = m_positionRectangle;
    DIRECTION desiredDirection = movementDirection;

    if (InputManager::getInstance().KeyDown(SDL_SCANCODE_W) ||
        InputManager::getInstance().KeyStillDown(SDL_SCANCODE_W)) {
        desiredDirection = UP;
    } else if (InputManager::getInstance().KeyDown(SDL_SCANCODE_A) ||
               InputManager::getInstance().KeyStillDown(SDL_SCANCODE_A)) {
        desiredDirection = LEFT;
    } else if (InputManager::getInstance().KeyDown(SDL_SCANCODE_S) ||
               InputManager::getInstance().KeyStillDown(SDL_SCANCODE_S)) {
        desiredDirection = DOWN;
    } else if (InputManager::getInstance().KeyDown(SDL_SCANCODE_D) ||
               InputManager::getInstance().KeyStillDown(SDL_SCANCODE_D)) {
        desiredDirection = RIGHT;
    }
    switch (desiredDirection) {
        case UP:
            desiredPosition.y -= m_movementSpeed;
            break;
        case DOWN:
            desiredPosition.y += m_movementSpeed;
            break;
        case RIGHT:
            desiredPosition.x += m_movementSpeed;
            break;
        case LEFT:
            desiredPosition.x -= m_movementSpeed;
            break;
        default:
            break;
    }

    bool collidedWithWall = false;
    for (auto &wall : Map::walls) {
        if (SDL_HasIntersection(&desiredPosition, &wall)) {
            collidedWithWall = true;
        }
    }

    if (!collidedWithWall) {
        movementDirection = desiredDirection;
    } else if (movementDirection == desiredDirection) {
        movementDirection = NONE;
    }

    switch (movementDirection) {
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
        default:
            break;
    }
}

std::string Player::getType() {
    return "Player";
}

