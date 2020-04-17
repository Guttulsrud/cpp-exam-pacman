#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/GameManager.h"
#include "../include/Pellet.h"
#include "../include/Ghost.h"
#include <SDL_mixer.h>
#include <future>
#include <fstream>

void Player::update() {

    SDL_Point potentialMovementDirection = updateMovementDirection();
    SDL_Rect potentialPosition = moveOneFrame(potentialMovementDirection);

    if (!willCollideWithWall(potentialPosition)) {
        m_positionRectangle = potentialPosition;
    } else {
        potentialPosition = moveOneFrame(movementChange);
        if (!willCollideWithWall(potentialPosition)) {
            m_positionRectangle = potentialPosition;
            potentialMovementDirection = movementChange;
        }
    }

    movementChange = potentialMovementDirection;
    updateDirection();
    m_animator.animate(&m_texture, m_direction);
    updateHitBox();
    moveInBoundsIfOutOfBounds();
}

SDL_Point Player::updateMovementDirection() {
    InputManager IM = InputManager::getInstance();
    SDL_Point potentialMovementChange = movementChange;
    if (!IM.KeyStillUp(SDL_SCANCODE_W) || !IM.KeyStillUp(SDL_SCANCODE_UP)) {
        potentialMovementChange.x = 0;
        potentialMovementChange.y = -m_movementSpeed;
    } else if (!IM.KeyStillUp(SDL_SCANCODE_A) || !IM.KeyStillUp(SDL_SCANCODE_LEFT)) {
        potentialMovementChange.x = -m_movementSpeed;
        potentialMovementChange.y = 0;
    } else if (!IM.KeyStillUp(SDL_SCANCODE_S) || !IM.KeyStillUp(SDL_SCANCODE_DOWN)) {
        potentialMovementChange.x = 0;
        potentialMovementChange.y = m_movementSpeed;
    } else if (!IM.KeyStillUp(SDL_SCANCODE_D) || !IM.KeyStillUp(SDL_SCANCODE_RIGHT)) {
        potentialMovementChange.x = m_movementSpeed;
        potentialMovementChange.y = 0;
    }
    return potentialMovementChange;
}

void Player::updateDirection() {
    if (movementChange.x > 0) {
        m_direction = RIGHT;
    } else if (movementChange.x < 0) {
        m_direction = LEFT;
    } else if (movementChange.y < 0) {
        m_direction = UP;
    } else if (movementChange.y > 0) {
        m_direction = DOWN;
    } else {
        m_direction = NONE;
    }
}

//is in use
void playDeathAnimation() {
    std::shared_ptr<Player> &player = GameManager::getPlayer();
    std::vector<std::shared_ptr<Stationary>> &stationary = GameManager::getStationery();
    std::vector<std::shared_ptr<Pellet>> &pellets = GameManager::getPellets();
    auto game = GameManager::getInstance();

    for (int i = 0; i < 45; i++) {
        for (auto const &s : stationary) {
            s->render();
        }
        for (auto const &pellet : pellets) {
            pellet->render();
        }

        player->deathAnimator.animate(&player->m_texture, player->m_direction);
        player->render();
        SDLManager::getInstance().renderBuffer();
        SDL_Delay(25);
    }
}



void Player::reset() {
    m_positionRectangle.x = 30 * 14.5;
    m_positionRectangle.y = 30 * 24;
    m_animator.animate(&m_texture, m_direction);
    updateHitBox();
}




void Player::die() {
    m_direction = UP;

}

bool Player::willCollideWithWall(SDL_Rect &possiblePosition) {
    for (auto &stationary : GameManager::getStationery()) {
        if (stationary->getType() == WALL && SDL_HasIntersection(&possiblePosition, &stationary->m_positionRectangle)) {
            return true;
        }
    }
    return false;
}

SDL_Rect Player::moveOneFrame(SDL_Point potentialChange) {
    SDL_Rect returnPosition = m_positionRectangle;
    returnPosition.x += potentialChange.x;
    returnPosition.y += potentialChange.y;
    return returnPosition;
}

void Player::playSound(Sound sound, int channel) {
    Mix_PlayChannel(channel, sounds[sound], 0);

}

