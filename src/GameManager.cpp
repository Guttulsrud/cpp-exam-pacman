#include <fstream>
#include "../include/GameManager.h"


void GameManager::run() {

    sdlManager.init("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 930, 1020);
    while (running) {
        sdlManager.renderStartScreen();
        waitForMenuInput();
        while (inGame) {
            runGameLoop();
            if (currentScore > highScore) {
                newHighScore = currentScore;
            }
        }
    }
}

void GameManager::writeHighScore(int score) {
    std::ofstream file;
    file.open("../resources/highscore.txt");
    if (file) {
        file << score;
    }
}


void removeEatenPellets(std::vector<std::shared_ptr<Pellet>> &pellets) {

    pellets.erase(
            std::remove_if(pellets.begin(), pellets.end(),
                           [](const std::shared_ptr<Pellet> &pellet) {
                               return pellet->eaten;
                           }),
            pellets.end());
}

void GameManager::update() {
    checkIfMapComplete();
    updateMovables();
    handleCollisions();
}

void GameManager::render() {
    renderTopDisplay();
    renderGameObjects();
    sdlManager.renderBuffer();
}

void GameManager::setMap(const int &mapIndex) {
    currentLevel = mapIndex;
    m_map = std::make_shared<Map>(levelPaths[mapIndex], mapIndex);
}

std::shared_ptr<Player> &GameManager::getPlayer() {
    return getInstance().m_player;
}

std::vector<std::shared_ptr<Stationary>> &GameManager::getStationery() {
    return getInstance().m_stationery;
}

void GameManager::addStationary(const std::shared_ptr<Stationary> &object) {
    getStationery().emplace_back(object);
}

void GameManager::createMovables() {

    m_player = std::make_shared<Player>(TextureManager::loadTexture("../resources/img/pacman/base.png"),
                                        30 * 14.5, 30 * 24, 3,
                                        EntityAnimator({{UP,
                                                                {
                                                                        "../resources/img/pacman/base.png",
                                                                        "../resources/img/pacman/medium-open-up.png",
                                                                        "../resources/img/pacman/large-open-up.png",
                                                                        "../resources/img/pacman/medium-open-up.png"
                                                                }
                                                        },
                                                        {DOWN,
                                                                {
                                                                        "../resources/img/pacman/base.png",
                                                                        "../resources/img/pacman/medium-open-down.png",
                                                                        "../resources/img/pacman/large-open-down.png",
                                                                        "../resources/img/pacman/medium-open-down.png"
                                                                }
                                                        },
                                                        {LEFT,
                                                                {
                                                                        "../resources/img/pacman/base.png",
                                                                        "../resources/img/pacman/medium-open-left.png",
                                                                        "../resources/img/pacman/large-open-left.png",
                                                                        "../resources/img/pacman/medium-open-left.png"
                                                                }
                                                        },
                                                        {RIGHT,
                                                                {
                                                                        "../resources/img/pacman/base.png",
                                                                        "../resources/img/pacman/medium-open-right.png",
                                                                        "../resources/img/pacman/large-open-right.png",
                                                                        "../resources/img/pacman/medium-open-right.png"
                                                                }
                                                        }})

    );
                                        30 * 14.5, 30 * 24, 0, 3);

    addGhost(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/green_E1.png"),
            30 * 13, 30 * 15, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/green_N1.png",
                                            "../resources/img/ghosts/green_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/green_S1.png",
                                            "../resources/img/ghosts/green_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/green_W1.png",
                                            "../resources/img/ghosts/green_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/green_E1.png",
                                            "../resources/img/ghosts/green_E2.png"
                                    }
                            }})));

    addGhost(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/orange_E1.png"),
            30 * 16, 30 * 15, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/purpleN1.png",
                                            "../resources/img/ghosts/purple_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/purple_S1.png",
                                            "../resources/img/ghosts/purple_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/purple_W1.png",
                                            "../resources/img/ghosts/purple_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/purple_E1.png",
                                            "../resources/img/ghosts/purple_E2.png"
                                    }
                            }})));

    addGhost(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/red_E1.png"),
            30 * 14 + 15, 30 * 12, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/red_N1.png",
                                            "../resources/img/ghosts/red_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/red_S1.png",
                                            "../resources/img/ghosts/red_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/red_W1.png",
                                            "../resources/img/ghosts/red_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/red_E1.png",
                                            "../resources/img/ghosts/red_E2.png"
                                    }
                            }})));

    addGhost(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/purple_E1.png"),
            30 * 14 + 15, 30 * 15, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/orange_N1.png",
                                            "../resources/img/ghosts/orange_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/orange_S1.png",
                                            "../resources/img/ghosts/orange_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/orange_W1.png",
                                            "../resources/img/ghosts/orange_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/orange_E1.png",
                                            "../resources/img/ghosts/orange_E2.png"
                                    }
                            }})));
}

void GameManager::startNewRound() {
    stopSoundOnChannel(-1);
    m_player->reset();

int GameManager::readHighScoreFromFile() {
    int score = 0;
    std::ifstream file("../resources/highscore.txt");
    if (file) {
        file >> score;
    }
    return score;
}

void GameManager::resetRound() {
    lives = 3;
    Mix_HaltChannel(-1);
    getPlayer()->reset();

    for (auto const &ghost : getGhosts()) {
        ghost->reset();
    }
    sdlManager.initFonts();
    render();
    m_player->playSound(INTRO, 5);
    stopExecutionWhileSoundPlaying(5);
}

void GameManager::gameOver() {
    currentLevel = 0;
    SDL_RenderClear(SDLManager::m_renderer);
    if (currentScore > highScore) {
        writeHighScore(currentScore);
    }
    m_pellets.clear();
    m_stationery.clear();
    m_ghosts.clear();
    inGame = false;
}

void GameManager::startGame() {
    numberOfLivesDisplayTexture = TextureManager::loadTexture("../resources/img/pacman/medium-open-right.png");
    sdlManager.initFonts();
    setMap(currentLevel);
    createMovables();
    startNewRound();
    inGame = true;
}

void GameManager::mapCompleted() {
    stopSoundOnChannel(-1);
    m_player->playSound(MAP_COMPLETED);
    stopExecutionWhileSoundPlaying(-1);
    m_stationery.clear();
    sdlManager.renderBuffer();

    currentLevel++;
    if (currentLevel == 3) {
        sdlManager.setFontSize(100);
        sdlManager.drawText("You win!", 200, 400);
        SDL_RenderPresent(SDLManager::m_renderer);
        SDL_Delay(3000);
        SDL_RenderClear(SDLManager::m_renderer);
        currentLevel = 0;
    }
    setMap(currentLevel);
    startNewRound();
}

void GameManager::renderTopDisplay() {
    if (newHighScore > highScore) {
        sdlManager.drawText("Highscore: %d", 35, 0, newHighScore);
    } else {
        sdlManager.drawText("Highscore: %d", 35, 0, highScore);
    }
    sdlManager.drawText("Score: %d", 400, 0, currentScore);

    auto sourceRect = SDL_Rect{0, 0, 1600, 1600};
    for (int i = 0; i < lives; i++) {
        auto destRect = SDL_Rect{780 + i * 40, 0, 30, 30};

        sdlManager.render(numberOfLivesDisplayTexture, &sourceRect, &destRect);
    }
}

void GameManager::renderGameObjects() {
    for (auto const &pellet : m_pellets) {
        if (pellet->m_isFruit) {
            if (currentScore > scoreLastRound + 200) {
                pellet->render();
            }
        } else {
            pellet->render();
        }
    }

    for (auto const &stationary : m_stationery) {
        stationary->render();
    }

    for (auto const &ghost : m_ghosts) {
        ghost->render();
    }

    m_player->render();
}

void GameManager::checkIfMapComplete() {
    if (m_pellets.empty()) {
        mapCompleted();
    } else {
        m_pellets.erase(std::remove_if(
                m_pellets.begin(), m_pellets.end(), [](auto &pellet) { return pellet->m_eaten; }),
                        m_pellets.end());
    }
}

void GameManager::addPellet(const std::shared_ptr<Pellet> &pellet) {
    getPellets().emplace_back(pellet);
}

void GameManager::addGhost(const std::shared_ptr<Ghost> &ghost) {
    getGhosts().emplace_back(ghost);
}

std::vector<std::shared_ptr<Pellet>> &GameManager::getPellets() {
    return getInstance().m_pellets;
}

std::vector<std::shared_ptr<Ghost>> &GameManager::getGhosts() {
    return getInstance().m_ghosts;
}

void GameManager::calculateAndDelayFrameTime() {
    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
    frameStart = SDL_GetTicks();
}

void GameManager::updateMovables() {
    for (auto const &ghost : m_ghosts) {
        ghost->update();
    }
    getPlayer()->update();
}

void GameManager::runGameLoop() {
    calculateAndDelayFrameTime();
    inputManager.update();
    update();
    if (inGame) {
        render();
    }
}

void GameManager::waitForMenuInput() {
    while (true) {
        if (inputManager.KeyDown(SDL_SCANCODE_SPACE)) {
            break;
        }
        if (inputManager.KeyDown(SDL_SCANCODE_Q)) {
            sdlManager.clean();
            running = false;
            inGame = false;
        }

        inputManager.update();
    }
    startGame();
}

void GameManager::stopSoundOnChannel(int channel) {
    Mix_HaltChannel(channel);
}

void GameManager::stopExecutionWhileSoundPlaying(int channel) {
    while (Mix_Playing(channel)) {}
}
void GameManager::handleCollisions() {
    checkForPelletPickup();
    checkForPlayerAndGhost();

    // Check for collision with stationary game objects
    bool collectedFruit = false;
    bool collectedPellet = false;

    for (auto &p : GameManager::getPellets()) {
        if (SDL_HasIntersection(&m_player->hitBox, &p->m_positionRectangle)) {
            collectedPellet = true;
            currentScore += 10;

            if (p->m_isPowerPellet) {
                playSound(EAT_POWER_PELLET,1);
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
        playSound(EAT_FRUIT,1);
        currentScore += 300;
    }
}

void GameManager::checkForPelletPickup() {

}


void playerDeathAnimation() {
    std::shared_ptr<Player> &player = GameManager::getPlayer();
    std::vector<std::shared_ptr<Stationary>> &stationary = GameManager::getStationery();
    auto game = GameManager::getInstance();

    for (int i = 0; i < 45; i++) {


        for (auto const &s : stationary) {
            s->render();
        }
        player->deathAnimator.animate(&player->m_texture, player->m_direction);
        player->render();
        SDLManager::getInstance().renderBuffer();
    }

}

void GameManager::checkForPlayerAndGhost() {

    for (auto &ghost : GameManager::getGhosts()) {
        if (SDL_HasIntersection(&m_player->hitBox, &ghost->hitBox)) {
            if (ghost->eatable) {
                //ghost is dead
                if (!ghost->dead) {
                    playSound(EAT_GHOST,2);
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
                m_player->die();



                lives--;
                playSound(DEATH,4);
                auto tread = std::async(playerDeathAnimation);

                while (Mix_Playing(-1)) {}
                if (lives < 1) {
                    tread.get();
                    gameOver();
                } else {
                    resetRound();
                }

            }
        }
    }
}

void GameManager::playSound(Sound sound, int channel) {
    Mix_PlayChannel(channel, sounds[sound], 0);
}




