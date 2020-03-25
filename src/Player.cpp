//
// Created by mathiss on 3/25/2020.
//

#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Game.h"

void Player::update() {

    SDL_Rect newPosition = m_positionRectangle;
    bool changedDirection = false;
    DIRECTION oldDirection = direction;

    if (InputManager::getInstance().KeyDown(SDL_SCANCODE_W)) {
        direction = UP;
        changedDirection = true;

    } else if (InputManager::getInstance().KeyDown(SDL_SCANCODE_A)) {
        direction = LEFT;
        changedDirection = true;

    } else if (InputManager::getInstance().KeyDown(SDL_SCANCODE_S)) {
        direction = DOWN;
        changedDirection = true;

    } else if (InputManager::getInstance().KeyDown(SDL_SCANCODE_D)) {
        direction = RIGHT;
        changedDirection = true;
    }

    switch (direction) {
        case UP:
            newPosition.y -= m_movementSpeed;
            break;
        case DOWN:
            newPosition.y += m_movementSpeed;
            break;
        case RIGHT:
            newPosition.x += m_movementSpeed;
            break;
        case LEFT:
            newPosition.x -= m_movementSpeed;
            break;
        default:
            break;
    }

    /// Collision
    bool collided = false;
    std::for_each(
            std::begin(Game::getGameObjects()), std::end(Game::getGameObjects()),
            [this, &collided, newPosition](std::shared_ptr<GameObject> &object) {
                if (m_id != object->m_id) {

                    if (SDL_HasIntersection(&newPosition, &object->m_positionRectangle)) {
                        collided = true;
                    }

                }
            }
    );


    if (!collided) {
        m_positionRectangle = newPosition;
    } else if(changedDirection){
        direction = oldDirection;
    }
    //////

}

