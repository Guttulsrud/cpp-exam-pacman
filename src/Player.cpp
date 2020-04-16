#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/GameManager.h"
#include "../include/Pellet.h"
#include "../include/Ghost.h"
#include <SDL_mixer.h>
#include <future>
#include <fstream>

using namespace std::chrono_literals;

void Player::update() {
    framesSinceTextureChange++;

    moveInBoundsIfOutOfBounds();

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

    if (currentScore > highScore) {
        newHighScore = currentScore;
    }
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

        player->deathAnimator.animate(&player->m_texture, player->direction);
        player->render();
        SDLManager::getInstance().renderBuffer();
        SDL_Delay(25);
    }
}

bool Player::positionIsValid(SDL_Rect &possiblePosition) {

    //Todo: refactor
    bool didNotCollideWithWall = true;


    // Check for collision with moving game objects
    for (auto &ghost : GameManager::getGhosts()) {
        if (SDL_HasIntersection(&hitBox, &ghost->hitBox)) {
            if (ghost->eatable) {
                if (!ghost->dead) {
                    playSound(EAT_GHOST);
                    playSound(GHOST_RETURN, 6);
                }
                ghost->m_movementSpeed = 5 ;
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
                    GameManager::getInstance().startNewRound();
                }

                return false;
            }
        }
    }


    // Check for collision with stationary game objects
    bool collectedFruit = false;
    bool collectedPellet = false;

    for (auto &p : GameManager::getPellets()) {
        if (SDL_HasIntersection(&possiblePosition, &p->m_positionRectangle)) {
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

    for (auto &stationary : GameManager::getStationery()) {
        if (stationary->getType() == WALL && SDL_HasIntersection(&possiblePosition, &stationary->m_positionRectangle)) {
            didNotCollideWithWall = false;
        }
    }

    if (collectedPellet && !Mix_Playing(1)) {
        playSound(EAT_PELLET, 1);

    } else if (collectedFruit) {
        playSound(EAT_FRUIT);
        currentScore += 300;
    }
    return didNotCollideWithWall;
}

void Player::writeHighScore(int score) {
    std::ofstream file;
    file.open("../resources/highscore.txt");
    if (file) {
        file << score;
    }
}

TYPE Player::getType() {
    return PLAYER;
}

void Player::reset() {
    m_positionRectangle.x = 30 * 14.5;
    m_positionRectangle.y = 30 * 24;
    m_animator.animate(&m_texture, direction);
    updateHitbox();
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

