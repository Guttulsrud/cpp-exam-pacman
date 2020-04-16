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
    handleStuffRefactorPls();
    updateHitBox();
    moveInBoundsIfOutOfBounds();

    if (currentScore > highScore) {
        newHighScore = currentScore;
    }
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

void Player::handleStuffRefactorPls() {

    //Todo: refactor

    // Check for collision with moving game objects
    for (auto &ghost : GameManager::getGhosts()) {
        if (SDL_HasIntersection(&hitBox, &ghost->hitBox)) {
            if (ghost->eatable) {
                if (!ghost->dead) {
                    playSound(EAT_GHOST);
                    playSound(GHOST_RETURN, 6);
                }
                ghost->m_movementSpeed = 5;
                ghost->dead = true;
                ghost->eatable = false;
                ghost->switchedToEatable = false;
            } else if (ghost->dead) {
                ghost->eatable = false;
                ghost->switchedToEatable = false;
            } else {
                lives--;
                playSound(DEATH);
                auto tread = std::async(playDeathAnimation);

                while (Mix_Playing(-1)) {}
                if (lives < 1) {
                    tread.get();
                    GameManager::getInstance().gameOver();
                } else {
                    GameManager::getInstance().resetRound();
                }
            }
        }
    }


    // Check for collision with stationary game objects
    bool collectedFruit = false;
    bool collectedPellet = false;

    for (auto &p : GameManager::getPellets()) {
        if (SDL_HasIntersection(&hitBox, &p->m_positionRectangle)) {
            collectedPellet = true;
            currentScore += 10;

            if (p->m_isPowerPellet) {
                playSound(EAT_POWER_PELLET);
                for (auto &ghost : GameManager::getGhosts()) {
                    ghost->switchedToEatable = true;
                    ghost->eatableStateEnd = false;
                    ghost->m_movementSpeed = 2;
                }

            } else if (p->m_isFruit) {
                collectedFruit = true;
                currentScore += 300;
            }
            p->eaten = true;

        }
    }

    if (collectedPellet && !Mix_Playing(1)) {
        playSound(EAT_PELLET, 1);

    } else if (collectedFruit) {
        playSound(EAT_FRUIT);
        currentScore += 300;
    }
}

void Player::writeHighScore(int score) {
    std::ofstream file;
    file.open("../resources/highscore.txt");
    if (file) {
        file << score;
    }
}

void Player::reset() {
    m_positionRectangle.x = 30 * 14.5;
    m_positionRectangle.y = 30 * 24;
    m_animator.animate(&m_texture, m_direction);
    updateHitBox();
    scoreLastRound = currentScore;
}

void Player::playSound(Sound sound, int channel) {
    Mix_PlayChannel(channel, sounds[sound], 0);
}

int Player::readHighScoreFromFile() {
    int score = 0;
    std::ifstream file("../resources/highscore.txt");
    if (file) {
        file >> score;
    }
    return score;
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

