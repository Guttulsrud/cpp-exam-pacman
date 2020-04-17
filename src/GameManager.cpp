#include <fstream>
#include "../include/GameManager.h"


void GameManager::run() {

    sdlManager.init("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 930, 1020);

    while (running) {
        sdlManager.renderStartScreen();
        while (true) {
            if (!inputManager.KeyStillUp(SDL_SCANCODE_SPACE)) {
                break;
            } else if (!inputManager.KeyStillUp(SDL_SCANCODE_Q)) {
                sdlManager.clean();
                running = false;
                inGame = false;
            }
            inputManager.update();
        }

        startGame();
        while (inGame) {
            calculateAndDelayFrameTime();
            inputManager.update();
            update();
            if (inGame) {
                render();
            }

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
    for (auto const &g : getGhosts()) {
        g->update();
    }

    checkForRemainingPelletsAndRemove();

    getPlayer()->update();
    handleCollisions();
}

void GameManager::render() {
    renderTopDisplay();
    renderGameObjects();

    sdlManager.renderBuffer();
}


void GameManager::setMap(const int &mapIndex) {
    currentLevel = mapIndex;
    map = std::make_shared<Map>(levelPaths[mapIndex], mapIndex);
}

std::shared_ptr<Player> &GameManager::getPlayer() {
    return getInstance().m_player;
}


std::vector<std::shared_ptr<Stationary>> &GameManager::getStationery() {
    return getInstance().stationery;
}

void GameManager::addStationary(const std::shared_ptr<Stationary> &object) {
    getStationery().emplace_back(object);
}

void GameManager::createMovables() {

    m_player = std::make_shared<Player>(TextureManager::loadTexture("../resources/img/pacman/base.png"),
                                        30 * 14.5, 30 * 24, 0, 3);



    //TODO: Draw with map class
    addGhost(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/green_E1.png"),
            30 * 13, 30 * 15, 0, 3,
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
            30 * 16, 30 * 15, 0, 3,
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
            30 * 14 + 15, 30 * 12, 0, 3,
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
            30 * 14 + 15, 30 * 15, 0, 3,
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
    playSound(INTRO, 5);
    while (Mix_Playing(5)) {}
    scoreLastRound = currentScore;
}

void GameManager::gameOver() {
    currentLevel = 0;
    SDL_RenderClear(SDLManager::m_renderer);
    if (currentScore > highScore) {
        writeHighScore(currentScore);
    }
    getGhosts().clear();
    getStationery().clear();
    getPellets().clear();
    inGame = false;
}

void GameManager::startGame() {
    numberOfLivesDisplayTexture = TextureManager::loadTexture("../resources/img/pacman/medium-open-right.png");
    sdlManager.initFonts();
    setMap(currentLevel);
    createMovables();
    resetRound();
    inGame = true;
}

void GameManager::mapCompleted() {
    Mix_HaltChannel(-1);
    playSound(MAP_COMPLETED, 10);
    while (Mix_Playing(-1)) {}

    getStationery().clear();
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
    resetRound();

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
    for (auto const &p : pellets) {
        p->render();
    }

    for (auto const &s : stationery) {
        s->render();
    }

    for (auto const &g : ghosts) {
        g->render();
    }

    m_player->render();
}

void GameManager::checkForRemainingPelletsAndRemove() {
    if (!getPellets().empty()) {
        removeEatenPellets(getPellets());
    } else {
        mapCompleted();
    }
}


void GameManager::addPellet(const std::shared_ptr<Pellet> &pellet) {
    getPellets().emplace_back(pellet);
}

void GameManager::addGhost(const std::shared_ptr<Ghost> &ghost) {
    getGhosts().emplace_back(ghost);
}

std::vector<std::shared_ptr<Pellet>> &GameManager::getPellets() {
    return getInstance().pellets;
}

std::vector<std::shared_ptr<Ghost>> &GameManager::getGhosts() {
    return getInstance().ghosts;
}

void GameManager::calculateAndDelayFrameTime() {
    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
    frameStart = SDL_GetTicks();
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




