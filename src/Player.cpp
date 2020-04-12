#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/Pellet.h"
#include "../include/Ghost.h"
#include <SDL_mixer.h>
#include <future>

using namespace std::chrono_literals;

void Player::update() {
    framesSinceTextureChange++;

    //NEW VOIDWARP
    //TODO: put voidwarp in method
    if(m_positionRectangle.x > 892){
        m_positionRectangle.x = -21;

    } else if(m_positionRectangle.x < -22){
        m_positionRectangle.x = 891;
    }

    SDL_Rect possiblePosition = m_positionRectangle;
    SDL_Point possibleMovementChange = movementChange;

    InputManager IM = InputManager::getInstance();
    if (!IM.KeyStillUp(SDL_SCANCODE_W) || !IM.KeyStillUp(SDL_SCANCODE_UP)) {
        possibleMovementChange.x = 0;
        possibleMovementChange.y = -m_movementSpeed;
    } else if (!IM.KeyStillUp(SDL_SCANCODE_A) || !IM.KeyStillUp(SDL_SCANCODE_LEFT)) {
        possibleMovementChange.x = -m_movementSpeed;
        possibleMovementChange.y = 0;
    } else if (!IM.KeyStillUp(SDL_SCANCODE_S) || !IM.KeyStillUp(SDL_SCANCODE_DOWN)) {
        possibleMovementChange.x = 0;
        possibleMovementChange.y = m_movementSpeed;
    } else if (!IM.KeyStillUp(SDL_SCANCODE_D) || !IM.KeyStillUp(SDL_SCANCODE_RIGHT)) {
        possibleMovementChange.x = m_movementSpeed;
        possibleMovementChange.y = 0;
        direction = RIGHT;
    }

    possiblePosition.x += possibleMovementChange.x;
    possiblePosition.y += possibleMovementChange.y;

    if (positionIsValid(possiblePosition)) {
        determineDirection(possiblePosition);
        m_positionRectangle = possiblePosition;
        m_animator.animate(&m_texture, direction);
    } else {
        possiblePosition = m_positionRectangle;
        possibleMovementChange = movementChange;

        possiblePosition.x += possibleMovementChange.x;
        possiblePosition.y += possibleMovementChange.y;
        if (positionIsValid(possiblePosition)) {
            determineDirection(possiblePosition);
            m_positionRectangle = possiblePosition;
            m_animator.animate(&m_texture, direction);
        }
    }
    movementChange = possibleMovementChange;
    updateHitbox();

}

void Player::determineDirection(const SDL_Rect &possiblePosition) {
    if (possiblePosition.x > m_positionRectangle.x) {
        direction = RIGHT;
    } else if (possiblePosition.x < m_positionRectangle.x) {
        direction = LEFT;
    } else if (possiblePosition.y < m_positionRectangle.y) {
        direction = UP;
    } else if (possiblePosition.y > m_positionRectangle.y) {
        direction = DOWN;
    } else {
        direction = NONE;
    }
}


bool Player::positionIsValid(SDL_Rect &possiblePosition) {
    bool didNotCollideWithWall = true;


    // Check for collision with moving game objects
    for (auto &movable : Game::getMovableGameObjects()) {
        if (SDL_HasIntersection(&hitbox, &movable->hitbox) && movable->getType() == GHOST) {
            auto ghost = dynamic_cast<Ghost *>(movable.get());
            if (ghost->powerPelletState) {
                if (!ghost->dead) {

                    playSound(EAT_GHOST, 3);
                }
                ghost->dead = true;
            } else {
                playSound(DEATH);
                lives < 1 ? Game::getInstance().gameOver() : Game::getInstance().Game::resetRound();
                return false;
            }
        }
    }


    // Check for collision with stationary game objects
    bool collectedPellet = false;
    for (auto &stationary : Game::getStationaryGameObjects()) {
        if (SDL_HasIntersection(&possiblePosition, &stationary->m_positionRectangle)) {
            if (stationary->getType() == WALL) {
                didNotCollideWithWall = false;
            }
            if (stationary->getType() == PELLET) {
                collectedPellet = true;


                if (dynamic_cast<Pellet *>(stationary.get())->m_isPowerPellet) {

                    playSound(EAT_POWER_PELLET, 2);


                    for (auto &o : Game::getMovableGameObjects()) {
                        if (o->getType() == GHOST) {
                            dynamic_cast<Ghost *>(o.get())->switchedToPowerPelletState = true;
                        }
                    }
                }
                dynamic_cast<Pellet *>(stationary.get())->eaten = true;
                points += 10;

            }
        }

    }
    if (collectedPellet && !Mix_Playing(1)) {
        playSound(EAT_PELLET, 1);
    }
    return didNotCollideWithWall;
}

TYPE Player::getType() {
    return PLAYER;
}

void Player::reset() {

    //todo: play death animation here
    lives--;
    m_positionRectangle.x = 30 * 14.5;
    m_positionRectangle.y = 30 * 24;
    updateHitbox();

}

void Player::playSound(Sound sound, int channel) {
    Mix_PlayChannel(channel, sounds[sound], 0);
}
