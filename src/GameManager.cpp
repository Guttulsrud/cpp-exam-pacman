#include "../include/GameManager.h"
#include "../include/Player.h"
#include "../include/Ghost.h"
#include "../include/Pellet.h"
#include "../include/InputManager.h"

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <fstream>

SDL_Renderer *GameManager::renderer = nullptr;

int GameManager::init(const char *title, int xPos, int yPos, int width, int height) {

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if (!window) {
            std::cout << "Couldn't open Window!" << std::endl;

        }

        renderer = SDL_CreateRenderer(window, -1, flags);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        } else {
            std::cout << "Couldn't create renderer" << std::endl;

        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)) {
            Mix_AllocateChannels(8);
        }

        if (TTF_Init() != 0) {
            std::cout << "Couldn't open TTF" << std::endl;
        }
    }
    isRunning() = true;

    return 0;
}

void GameManager::run() {

    init("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 930, 1020);

    while (GameManager::isRunning()) {
        renderStartScreen();
        while (true) {
            if (!inputManager.KeyStillUp(SDL_SCANCODE_SPACE)) {
                break;
            } else if (!inputManager.KeyStillUp(SDL_SCANCODE_Q)) {
                clean();
            }
            inputManager.update();
        }

        startGame();
        while (GameManager::isInGame()) {
            calculateAndDelayFrameTime();
            inputManager.update();
            update();
            if(GameManager::isInGame()) {
                render();
            }
        }
    }
}


void GameManager::renderStartScreen() {


    auto startScreenRect = SDL_Rect{0, 0, 930, 1020};

    SDL_RenderCopy(renderer, TextureManager::loadTexture(
            "../resources/startscreenassets/start_screen_alt.png"), &startScreenRect, &startScreenRect);

    font = FC_CreateFont();
    FC_LoadFont(font, renderer, "../resources/fonts/arial.ttf", 30, FC_MakeColor(240, 153, 63, 255), TTF_STYLE_BOLD);
    FC_Draw(font, renderer, 295, 380, "Press Space to start!");
    FC_Draw(font, renderer, 330, 550, "Press 'Q' to quit!");

    FC_FreeFont(font);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);


}

void removeEatenPellets(std::vector<std::shared_ptr<Pellet>> &pellets) {

    pellets.erase(
            std::remove_if(pellets.begin(), pellets.end(),
                           [](const std::shared_ptr<Pellet> &pellet) {
                               return pellet.get()->eaten;
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

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void GameManager::clean() {
    TTF_Quit();
    FC_FreeFont(font);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Cleaned.." << std::endl;
}


void GameManager::setMap(const int &mapIndex) {
    currentLevel = mapIndex;
    map = std::make_shared<Map>(levelPaths[mapIndex], mapIndex);
}

void GameManager::setPlayer(std::shared_ptr<Player> const &object) {
    getInstance().m_player = object;
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

void GameManager::addMovables() {

    setPlayer(std::make_shared<Player>(TextureManager::loadTexture("../resources/img/pacman/base.png"),
                                       30 * 14.5, 30 * 24, 0, 3,
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

    ));



    //TODO: Draw with map class
    addGhost(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/green_E1.png"),
            30 * 15, 30 * 15, 0, 3,
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
            30 * 15, 30 * 15, 0, 3,
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
            30 * 15, 30 * 15, 0, 3,
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
            30 * 15, 30 * 15, 0, 3,
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
    initFonts();
    render();
    getPlayer()->playSound(INTRO, 5);
    while (Mix_Playing(5)) {}
}

void GameManager::gameOver() {
    currentLevel = 0;
    SDL_RenderClear(renderer);
    if (getPlayer()->currentScore > getPlayer()->highScore) {
        getPlayer()->writeHighScore(getPlayer()->currentScore);
    }
    getGhosts().clear();
    getStationery().clear();
    getPellets().clear();
    isInGame() = false;
}


void GameManager::startGame() {
    numberOfLivesDisplayTexture = TextureManager::loadTexture("../resources/img/pacman/medium-open-right.png");

    initFonts();
    setMap(currentLevel);
    addMovables();
    resetRound();
    isInGame() = true;
    getPellets();
}


void GameManager::initFonts() {
    initFont(42);
    drawText("Ready!", 375, 545);
    initFont(24);
}


void GameManager::drawText(const char *text, float x, float y, int parameter) {
    FC_Draw(font, renderer, x, y, text, parameter);
}


void GameManager::initFont(int size) {
    font = FC_CreateFont();
    FC_LoadFont(font, renderer, "../resources/fonts/arial.ttf", size, FC_MakeColor(255, 255, 0, 255), TTF_STYLE_NORMAL);
}

void GameManager::mapCompleted() {
    Mix_HaltChannel(-1);
    getPlayer()->playSound(MAP_COMPLETED);
    while (Mix_Playing(-1)) {}

    getStationery().clear();
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    currentLevel++;

    if (currentLevel == 3) {
        initFont(100);
        drawText("You win!", 200, 400);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
        SDL_RenderClear(renderer);
        currentLevel = 0;
    }

    setMap(currentLevel);
    resetRound();

}


void GameManager::renderTopDisplay() {
    if (getPlayer()->newHighScore > getPlayer()->highScore) {
        drawText("Highscore: %d", 35, 0, getPlayer()->newHighScore);
    } else {
        drawText("Highscore: %d", 35, 0, getPlayer()->highScore);
    }
    drawText("Score: %d", 400, 0, getPlayer()->currentScore);

    auto sourceRect = SDL_Rect{0, 0, 1600, 1600};
    for (int i = 0; i < getPlayer()->lives; i++) {
        auto destRect = SDL_Rect{780 + i * 40, 0, 30, 30};
        SDL_RenderCopy(renderer, numberOfLivesDisplayTexture, &sourceRect, &destRect);
    }

}

void GameManager::renderGameObjects() {
    std::vector<std::shared_ptr<Stationary>> &stationary = getStationery();
    std::vector<std::shared_ptr<Pellet>> &pelletObjects = getPellets();
    std::vector<std::shared_ptr<Ghost>> &ghostObjects = getGhosts();

    for (auto const &p : pelletObjects) {
        p->render();
    }

    for (auto const &s : stationary) {
        s->render();
    }

    for (auto const &g : ghostObjects) {
        g->render();
    }

    getPlayer()->render();
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





