//
// Created by mathiss on 3/25/2020.
//

#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Map.h"
#include "../include/Game.h"
#include "../include/TextureManager.h"
#include <iostream>
SDL_Texture *kek = Game::loadTexture("../resources/img/blue.png");

void Player::update() {
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

//    bool collidedWithWall = false;
//    for (auto &wall : Map::walls) {
//        if (SDL_HasIntersection(&desiredPosition, &wall)) {
//            collidedWithWall = true;
//        }
//    }
//
//    for (auto &pellet : Map::pellets) {
//
//        if (SDL_HasIntersection(&m_positionRectangle, &pellet)) {
//
//        }
//    }




//    if (!collidedWithWall) {
//        movementDirection = desiredDirection;
//    } else if (movementDirection == desiredDirection) {
//        movementDirection = NONE;
//    }

    desiredPosition = m_positionRectangle;
    switch (movementDirection) {
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
//    collidedWithWall = false;
//    for (auto &wall : Map::walls) {
//        if (SDL_HasIntersection(&desiredPosition, &wall)) {
//            collidedWithWall = true;
//        }
//    }
//    if(!collidedWithWall){
//        m_positionRectangle = desiredPosition;
//    }
}

std::string Player::getType() {
    return "Player";
}

