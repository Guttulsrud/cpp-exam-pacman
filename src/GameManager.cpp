#include <fstream>
#include "../include/GameManager.h"


void GameManager::run() {

    sdlManager.init("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 930, 1020);
    m_highScore = readHighScoreFromFile();
    sdlManager.initSounds();

    while (running) {
        sdlManager.renderStartScreen();
        waitForMenuInput();
        while (inGame) {
            runGameLoop();
            if (m_currentScore > m_highScore) {
                m_newHighScore = m_currentScore;
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
    m_map = std::make_shared<Map>(m_levelPaths[mapIndex], mapIndex);
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

    m_player = std::make_shared<Player>(
            30 * 14.5, 30 * 24, 3);

    addGhost(std::make_shared<Ghost>(
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

    addGhost(std::make_shared<Ghost>(30 * 14 + 15, 30 * 12, 3,
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
    sdlManager.stopSoundOnChannel(-1);
    m_player->reset();

    Mix_HaltChannel(-1);

    for (auto const &ghost : m_ghosts) {
        ghost->reset();
    }
    sdlManager.initFonts();
    render();
    sdlManager.playSound(INTRO, 5);
    sdlManager.stopExecutionWhileSoundPlaying(5);
}

int GameManager::readHighScoreFromFile() {
    int score = 0;
    std::ifstream file("../resources/highscore.txt");
    if (file) {
        file >> score;
    }
    return score;
}

void GameManager::gameOver() {
    sdlManager.stopSoundOnChannel(-1);
    currentLevel = 0;
    m_lives = 3;
    SDL_RenderClear(SDLManager::m_renderer);
    if (m_currentScore > m_highScore) {
        writeHighScore(m_currentScore);
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
    m_currentScore = 0;
}

void GameManager::mapCompleted() {
    sdlManager.stopSoundOnChannel(-1);
    sdlManager.playSound(MAP_COMPLETED);
    sdlManager.stopExecutionWhileSoundPlaying(-1);
    m_stationery.clear();
    sdlManager.renderBuffer();

    m_scoreLastRound = m_currentScore;
    currentLevel++;
    if (currentLevel == 3) {
        sdlManager.setFontSize(100);
        sdlManager.drawText("You win!", 300, 400);
        SDL_RenderPresent(SDLManager::m_renderer);
        SDL_Delay(3000);
        SDL_RenderClear(SDLManager::m_renderer);
        currentLevel = 0;
    }
    setMap(currentLevel);
    startNewRound();
}

void GameManager::renderTopDisplay() {
    if (m_newHighScore > m_highScore) {
        sdlManager.drawText("Highscore: %d", 35, 0, m_newHighScore);
    } else {
        sdlManager.drawText("Highscore: %d", 35, 0, m_highScore);
    }
    sdlManager.drawText("Score: %d", 400, 0, m_currentScore);

    auto sourceRect = SDL_Rect{0, 0, 1600, 1600};
    for (int i = 0; i < m_lives; i++) {
        auto destRect = SDL_Rect{780 + i * 40, 0, 30, 30};

        sdlManager.render(numberOfLivesDisplayTexture, &sourceRect, &destRect);
    }
}

void GameManager::renderGameObjects() {
    for (auto const &pellet : m_pellets) {
        if (pellet->m_isFruit) {
            if (m_currentScore > m_scoreLastRound + 500) {
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
    m_frameTime = SDL_GetTicks() - m_frameStart;

    if (frameDelay > m_frameTime) {
        SDL_Delay(frameDelay - m_frameTime);
    }
    m_frameStart = SDL_GetTicks();
}

void GameManager::updateMovables() {
    for (auto const &ghost : m_ghosts) {
        ghost->update();
    }
    m_player->update();
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
        if (inputManager.keyDown(SDL_SCANCODE_SPACE)) {
            break;
        }
        if (inputManager.keyDown(SDL_SCANCODE_Q)) {
            sdlManager.clean();
            running = false;
            inGame = false;
        }

        inputManager.update();
    }
    startGame();
}


void GameManager::handleCollisions() {
    checkForPlayerAndGhost();

    // Check for collision with stationary game objects
    bool collectedFruit = false;
    bool collectedPellet = false;

    for (auto &pellet : m_pellets) {
        if (SDL_HasIntersection(&m_player->m_hitBox, &pellet->m_positionRectangle)) {
            collectedPellet = true;
            m_currentScore += 10;

            if (pellet->m_isPowerPellet) {
                if(!Mix_Playing(3)) {
                    sdlManager.playSound(EAT_POWER_PELLET, 3);
                }
                for (auto &ghost : m_ghosts) {
                    ghost->powerPelletState();
                }

            } else if (pellet->m_isFruit) {
                collectedFruit = true;
                m_currentScore += 300;
            }
            pellet->m_eaten = true;

        }
    }

    if (collectedPellet && !Mix_Playing(1)) {
        sdlManager.playSound(EAT_PELLET, 1);

    } else if (collectedFruit) {
        sdlManager.playSound(EAT_FRUIT,1);
        m_currentScore += 300;
    }
}


//Has to be outside of GameManager
void playerDeathAnimation() {
    std::shared_ptr<Player> &player = GameManager::getPlayer();
    std::vector<std::shared_ptr<Stationary>> &stationary = GameManager::getStationery();
    std::vector<std::shared_ptr<Pellet>> &pellets = GameManager::getPellets();
    auto game = GameManager::getInstance();

    for (int i = 0; i < 45; i++) {

        for (auto const &p : pellets) {
            if (!p->m_isFruit)
                p->render();
        }
        for (auto const &s : stationary) {
            s->render();
        }

        player->deathAnimator.animate(&player->m_texture, player->m_direction);
        player->render();
        SDLManager::getInstance().renderBuffer();
    }

}

void GameManager::checkForPlayerAndGhost() {

    for (auto &ghost : m_ghosts) {
        if (SDL_HasIntersection(&m_player->m_hitBox, &ghost->m_hitBox)) {
            if (ghost->m_eatable) {
                ghostDead(ghost);
            } else if (!ghost->m_dead) {
                playerDead();
            }
        }
    }
}

void GameManager::ghostDead(std::shared_ptr<Ghost> &ghost) {
    if (!ghost->m_dead) {
        sdlManager.playSound(EAT_GHOST, 2);
        sdlManager.playSound(GHOST_RETURN, 6);
    }
    m_currentScore+=200;
    ghost->die();
}

void GameManager::playerDead() {
    m_player->die();
    sdlManager.stopSoundOnChannel(-1);
    m_lives--;
    sdlManager.playSound(DEATH);
    auto tread = std::async(playerDeathAnimation);

    sdlManager.stopExecutionWhileSoundPlaying(-1);
    if (m_lives < 1) {
        tread.get();
        gameOver();
    } else {
        startNewRound();
    }
}






