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
        }
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



    //TODO: Draw with map class
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

void GameManager::resetRound() {
    Mix_HaltChannel(-1);
    getPlayer()->reset();

    for (auto const &ghost : getGhosts()) {
        ghost->reset();
    }
    sdlManager.initFonts();
    render();
    getPlayer()->playSound(INTRO, 5);
    while (Mix_Playing(5)) {}
}

void GameManager::gameOver() {
    currentLevel = 0;
    SDL_RenderClear(SDLManager::m_renderer);
    if (getPlayer()->currentScore > getPlayer()->highScore) {
        getPlayer()->writeHighScore(getPlayer()->currentScore);
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
    getPlayer()->playSound(MAP_COMPLETED);
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
    if (getPlayer()->newHighScore > getPlayer()->highScore) {
        sdlManager.drawText("Highscore: %d", 35, 0, getPlayer()->newHighScore);
    } else {
        sdlManager.drawText("Highscore: %d", 35, 0, getPlayer()->highScore);
    }
    sdlManager.drawText("Score: %d", 400, 0, getPlayer()->currentScore);

    auto sourceRect = SDL_Rect{0, 0, 1600, 1600};
    for (int i = 0; i < getPlayer()->lives; i++) {
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





