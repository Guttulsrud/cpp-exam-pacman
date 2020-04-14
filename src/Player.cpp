#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/GameManager.h"
#include "../include/Pellet.h"
#include "../include/Ghost.h"
#include "../include/Fruit.h"
#include <SDL_mixer.h>
#include <future>
#include <fstream>

using namespace std::chrono_literals;

void Player::update() {
    framesSinceTextureChange++;

    //NEW VOIDWARP
    //TODO: put voidwarp in method
    if (m_positionRectangle.x > 892) {
        m_positionRectangle.x = -21;

    } else if (m_positionRectangle.x < -22) {
        m_positionRectangle.x = 891;
    }

    if (m_positionRectangle.y > 960) {
        m_positionRectangle.y = -21;

    } else if (m_positionRectangle.y < -22) {
        m_positionRectangle.y = 960;
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
    auto game = GameManager::getInstance();

    for (int i = 0; i < 45; i++) {


        for (auto const &s : stationary) {
            s->render();
        }
        player->deathAnimator.animate(&player->m_texture, player->direction);
        player->render();
        SDL_RenderPresent(GameManager::renderer);
        SDL_RenderClear(GameManager::renderer);
    }
}

bool Player::positionIsValid(SDL_Rect &possiblePosition) {
    bool didNotCollideWithWall = true;


    // Check for collision with moving game objects
    for (auto &movable : GameManager::getMovables()) {
        if (SDL_HasIntersection(&hitbox, &movable->hitbox) && movable->getType() == GHOST) {
            auto ghost = dynamic_cast<Ghost *>(movable.get());
            if (ghost->eatable) {
                if (!ghost->dead) {
                    //todo: Alle ghost return lyder stopper når et spøkelse kommer hjem
                    playSound(EAT_GHOST);
                    playSound(GHOST_RETURN, 6);
                }
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
                lives < 1 ? GameManager::getInstance().gameOver() : GameManager::getInstance().resetRound();

                return false;
            }
        }
    }


    // Check for collision with stationary game objects
    bool collectedFruit = false;
    bool collectedPellet = false;
    for (auto &stationary : GameManager::getStationery()) {
        if (SDL_HasIntersection(&possiblePosition, &stationary->m_positionRectangle)) {
            if (stationary->getType() == WALL) {
                didNotCollideWithWall = false;
            }
            if (stationary->getType() == PELLET) {
                collectedPellet = true;


                if (dynamic_cast<Pellet *>(stationary.get())->m_isPowerPellet) {

                    playSound(EAT_POWER_PELLET);


                    for (auto &o : GameManager::getMovables()) {
                        if (o->getType() == GHOST) {
                            dynamic_cast<Ghost *>(o.get())->switchedToEatable = true;
                            dynamic_cast<Ghost *>(o.get())->eatableStateEnd = false;
                        }
                    }
                }
                dynamic_cast<Pellet *>(stationary.get())->eaten = true;
                currentScore += 10;

            }
            if (stationary->getType() == FRUIT) {
                collectedFruit = true;
                dynamic_cast<Fruit *>(stationary.get())->eaten = true;
                currentScore += 300;
                //TODO: Fix indivudual currentScore for different types of fruits
            }
        }

    }
    if (collectedPellet && !Mix_Playing(1)) {
        playSound(EAT_PELLET, 1);
    }
    if (collectedFruit) {
        playSound(EAT_FRUIT);
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

}

void Player::playSound(Sound sound, int channel) {
    Mix_PlayChannel(channel, sounds[sound], 0);
}

int Player::readHighScore() {
    int score = 0;
    std::ifstream file("../resources/highscore.txt");
    if (file) {
        file >> score;
    }
    return score;
}

