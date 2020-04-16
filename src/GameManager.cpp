#include "../include/GameManager.h"


void GameManager::run() {

    sdlManager.init("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 930, 1020);
    while (running) {
        sdlManager.renderStartScreen();
        waitForMenuInput();
        while (inGame) {
            runGameLoop();
        }
    }
}

void GameManager::update() {
    checkIfMapComplete();
    updateMovables();
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
    if (m_player->currentScore > m_player->highScore) {
        m_player->writeHighScore(m_player->currentScore);
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
    if (m_player->newHighScore > m_player->highScore) {
        sdlManager.drawText("Highscore: %d", 35, 0, m_player->newHighScore);
    } else {
        sdlManager.drawText("Highscore: %d", 35, 0, m_player->highScore);
    }
    sdlManager.drawText("Score: %d", 400, 0, m_player->currentScore);

    auto sourceRect = SDL_Rect{0, 0, 1600, 1600};
    for (int i = 0; i < m_player->lives; i++) {
        auto destRect = SDL_Rect{780 + i * 40, 0, 30, 30};

        sdlManager.render(numberOfLivesDisplayTexture, &sourceRect, &destRect);
    }
}

void GameManager::renderGameObjects() {
    for (auto const &p : m_pellets) {
        if (p->m_isFruit) {
            if (m_player->currentScore > m_player->scoreLastRound + 200) {
                p->render();
            }
        } else {
            p->render();
        }
    }

    for (auto const &s : m_stationery) {
        s->render();
    }

    for (auto const &g : m_ghosts) {
        g->render();
    }

    m_player->render();
}

void GameManager::checkIfMapComplete() {
    if (m_pellets.empty()) {
        mapCompleted();
    } else {
        m_pellets.erase(std::remove_if(
                m_pellets.begin(), m_pellets.end(), [](auto &pellet) { return pellet->eaten; }),
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
    for (auto const &g : m_ghosts) {
        g->update();
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
}

void GameManager::stopSoundOnChannel(int channel) {
    Mix_HaltChannel(channel);
}

void GameManager::stopExecutionWhileSoundPlaying(int channel) {
    while (Mix_Playing(channel)) {}
}




