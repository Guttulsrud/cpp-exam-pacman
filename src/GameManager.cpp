#include "../include/GameManager.h"
#include "../include/Player.h"
#include "../include/Ghost.h"
#include "../include/Pellet.h"
#include "../include/InputManager.h"
#include "../include/Fruit.h"

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <fstream>

SDL_Renderer *GameManager::renderer = nullptr;

int GameManager::init(const char *title, int xPos, int yPos, int width, int height) {

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
            // Error message if can't initialize
        }

        Mix_AllocateChannels(8);

        if (window) {
        }

        renderer = SDL_CreateRenderer(window, -1, flags);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }

        if (TTF_Init() == 0) {
            std::cout << "TTF init" << std::endl;
        }

        std::cout << "GameManager running" << std::endl;
        isRunning = true;

    }
    return 0;
}

void GameManager::renderStartScreen() {
    InputManager IM = InputManager::getInstance();

    SDL_Texture *startScreenTexture = TextureManager::loadTexture(
            "../resources/startscreenassets/start_screen_alt.png");

    SDL_Rect startScreenRect = SDL_Rect{0, 0, 930, 1020};

    SDL_RenderCopy(GameManager::renderer, startScreenTexture, &startScreenRect, &startScreenRect);

    font = FC_CreateFont();
    FC_LoadFont(font, renderer, "../resources/fonts/arial.ttf", 30, FC_MakeColor(240, 153, 63, 255), TTF_STYLE_BOLD);
    FC_Draw(font, renderer, 295, 380, "Press Space to start!");
    FC_Draw(font, renderer, 330, 550, "Press 'Q' to quit!");

    FC_FreeFont(font);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    while (true) {
        if (!IM.KeyStillUp(SDL_SCANCODE_SPACE)) {
            break;
        } else if (!IM.KeyStillUp(SDL_SCANCODE_Q)) {
            abort();
        }
        IM.update();
    }

}

void removeFruit(std::vector<std::shared_ptr<Stationary>> &objects) {
    objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                           [](const std::shared_ptr<Stationary> &fruit) {
                               return fruit->getType() == FRUIT && dynamic_cast<Fruit *>(fruit.get())->eaten;
                           }),
            objects.end());
}

void removeEatenPellets(std::vector<std::shared_ptr<Stationary>> &objects) {

    objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                           [](const std::shared_ptr<Stationary> &pellet) {
                               return pellet->getType() == PELLET && dynamic_cast<Pellet *>(pellet.get())->eaten;
                           }),
            objects.end());
}

void GameManager::update() {
    std::vector<std::shared_ptr<Movable>> &movables = GameManager::getMovableGameObjects();
    std::shared_ptr<Player> &player = GameManager::getPlayer();

    player->update();

    for (auto const &m : movables) {
        m->update();
    }
    removeFruit(GameManager::getStationaryGameObjects());
    if (pelletsAreRemaining()) {
        removeEatenPellets(GameManager::getStationaryGameObjects());
    } else {

        mapCompleted();
    }
}

void GameManager::render() {
    std::vector<std::shared_ptr<Movable>> &movables = GameManager::getMovableGameObjects();
    std::vector<std::shared_ptr<Stationary>> &stationary = GameManager::getStationaryGameObjects();
    std::shared_ptr<Player> &player = GameManager::getPlayer();

    for (auto const &m :movables) {
        m->render();
    }
    for (auto const &s : stationary) {
        s->render();
    }

    if (player->newHighScore > player->highScore) {
        drawText("Highscore: %d", 35, 0, player->newHighScore);
    } else {
        drawText("Highscore: %d", 35, 0, player->highScore);
    }
    drawText("Points: %d", 400, 0, player->points);
    drawText("Lives: %d", 775, 0, player->lives);
    player->render();
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


void GameManager::setMap(int map) {
    switch (map) {
        case 1:
            maps[1] = std::make_shared<Map>("../resources/maps/level_one.txt");
            break;
        case 2:
            maps[2] = std::make_shared<Map>("../resources/maps/level_two.txt");
            break;
        case 3:
            maps[3] = std::make_shared<Map>("../resources/maps/level_three.txt");
            break;
        default:
            maps[1] = std::make_shared<Map>("../resources/maps/level_one.txt");
    }
    activeMap = map;
}

void GameManager::setPlayer(std::shared_ptr<Player> const &object) {
    getInstance().m_player = object;
}


std::shared_ptr<Player> &GameManager::getPlayer() {
    return getInstance().m_player;
}

std::vector<std::shared_ptr<Movable>> &GameManager::getMovableGameObjects() {
    return getInstance().movableGameObjects;
}

void GameManager::addMovableGameObject(const std::shared_ptr<Movable> &object) {
    getMovableGameObjects().emplace_back(object);
}

std::vector<std::shared_ptr<Stationary>> &GameManager::getStationaryGameObjects() {
    return getInstance().stationaryGameObjects;
}

void GameManager::addStationaryGameObject(const std::shared_ptr<Stationary> &object) {
    getStationaryGameObjects().emplace_back(object);
}

void GameManager::setGameObjects() {

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
    addMovableGameObject(std::make_shared<Ghost>(
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

    addMovableGameObject(std::make_shared<Ghost>(
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

    addMovableGameObject(std::make_shared<Ghost>(
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

    addMovableGameObject(std::make_shared<Ghost>(
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

    for (auto const &ghost : getMovableGameObjects()) {
        ghost->reset();
    }
    initFonts();
    render();
    getPlayer()->playSound(INTRO, 5);
    while (Mix_Playing(5)) {}
}

void GameManager::gameOver() {
    if (getPlayer()->points > getPlayer()->highScore) {
        getPlayer()->writeHighScore(getPlayer()->points);
    }
    getStationaryGameObjects().clear();

    initFont(40);
    drawText("Press space to play again", 150, 500);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    InputManager IM = InputManager::getInstance();

    while (!IM.KeyDown(SDL_SCANCODE_SPACE)) {
        IM.update();
    }

    setMap(1);
    getPlayer()->lives = 3;
    getPlayer()->points = 0;

    resetRound();
}


void GameManager::startGame() {
    initFonts();
    setGameObjects();
    setMap(1);
    render();
    resetRound();
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
    FC_LoadFont(font, renderer, "../resources/fonts/arial.ttf", size, FC_MakeColor(255, 255, 0, 255), TTF_STYLE_ITALIC);
}

void GameManager::mapCompleted() {
    Mix_HaltChannel(-1);
    getPlayer()->playSound(MAP_COMPLETED);
    while(Mix_Playing(-1)){}

    getStationaryGameObjects().clear();
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    if (activeMap > 2) {
        initFont(100);
        drawText("You win!", 200, 400);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
        SDL_RenderClear(renderer);
        activeMap = 1;
        setMap(activeMap);
        resetRound();

    } else {
        activeMap++;
        setMap(activeMap);
        resetRound();
    }
}

bool GameManager::pelletsAreRemaining() {
    int pelletsRemaining = 0;

    for (auto &p : GameManager::getStationaryGameObjects()) {
        if (p->getType() == PELLET) {
            pelletsRemaining++;
        }
    }

    return pelletsRemaining > 0;
}


