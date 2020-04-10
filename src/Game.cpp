#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Ghost.h"
#include "../include/VoidWarp.h"
#include "../include/Pellet.h"

#include <SDL2/SDL.h>

SDL_Renderer *Game::renderer = nullptr;


int Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if (window) {
        }

        renderer = SDL_CreateRenderer(window, -1, flags);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        std::cout << "Game running" << std::endl;
        isRunning = true;
        setGameObjects();
    }
    return 0;
}

void removeEatenPellets(std::vector<std::shared_ptr<StationaryObject>> &objects) {

    objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                           [](const std::shared_ptr<StationaryObject> &pellet) {
                               return pellet->getType() == PELLET && dynamic_cast<Pellet *>(pellet.get())->eaten;
                           }),
            objects.end());
}


void Game::update() {
    std::vector<std::shared_ptr<MovableObject>> &movables = Game::getMovableGameObjects();
    std::shared_ptr<Player> &player = Game::getPlayer();

    player->update();

    for (auto const &m : movables) {
        m->update();
    }


    removeEatenPellets(Game::getStationaryGameObjects());
}


void Game::render() {
    SDL_RenderClear(renderer);
    std::vector<std::shared_ptr<MovableObject>> &movables = Game::getMovableGameObjects();
    std::vector<std::shared_ptr<StationaryObject>> &stationary = Game::getStationaryGameObjects();
    std::shared_ptr<Player> &player = Game::getPlayer();

    for (auto const &m :movables) {
        m->render();
    }
    for (auto const &s : stationary) {
        s->render();
    }
    player->render();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned.." << std::endl;
}


void Game::addMap(const std::shared_ptr<Map> &m) {
    getMaps().emplace_back(m);
}

void Game::setPlayer(std::shared_ptr<Player> const &object) {
    getInstance().m_player = object;
}


std::shared_ptr<Map> &Game::getMap(int levelNumber) {
    return getMaps()[levelNumber-1];
}

Game::~Game() {

}

std::shared_ptr<Player> &Game::getPlayer() {
    return getInstance().m_player;
}

std::vector<std::shared_ptr<MovableObject>> &Game::getMovableGameObjects() {
    return getInstance().movableGameObjects;
}

void Game::addMovableGameObject(const std::shared_ptr<MovableObject> &object) {
    getMovableGameObjects().emplace_back(object);
}

std::vector<std::shared_ptr<StationaryObject>> &Game::getStationaryGameObjects() {
    return getInstance().stationaryGameObjects;
}

void Game::addStationaryGameObject(const std::shared_ptr<StationaryObject> &object) {
    getStationaryGameObjects().emplace_back(object);
}

void Game::setGameObjects() {

    setPlayer(std::make_shared<Player>(TextureManager::loadTexture("../resources/img/pacman/base.png"),
                                       30 * 15, 30 * 18, 0, 3,
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
            TextureManager::loadTexture("../resources/img/ghosts/green_ghost_E1.png"),
            30 * 15, 30 * 15, 0, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/green_ghost_N1.png",
                                            "../resources/img/ghosts/green_ghost_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/green_ghost_S1.png",
                                            "../resources/img/ghosts/green_ghost_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/green_ghost_W1.png",
                                            "../resources/img/ghosts/green_ghost_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/green_ghost_E1.png",
                                            "../resources/img/ghosts/green_ghost_E2.png"
                                    }
                            }})));

    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/orange_ghost_E1.png"),
            30 * 15, 30 * 15, 0, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/purple_ghost_N1.png",
                                            "../resources/img/ghosts/purple_ghost_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/purple_ghost_S1.png",
                                            "../resources/img/ghosts/purple_ghost_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/purple_ghost_W1.png",
                                            "../resources/img/ghosts/purple_ghost_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/purple_ghost_E1.png",
                                            "../resources/img/ghosts/purple_ghost_E2.png"
                                    }
                            }})));

    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/red_ghost_E1.png"),
            30 * 15, 30 * 15, 0, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/red_ghost_N1.png",
                                            "../resources/img/ghosts/red_ghost_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/red_ghost_S1.png",
                                            "../resources/img/ghosts/red_ghost_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/red_ghost_W1.png",
                                            "../resources/img/ghosts/red_ghost_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/red_ghost_E1.png",
                                            "../resources/img/ghosts/red_ghost_E2.png"
                                    }
                            }})));

    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/purple_ghost_E1.png"),
            30 * 15, 30 * 15, 0, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/orange_ghost_N1.png",
                                            "../resources/img/ghosts/orange_ghost_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/orange_ghost_S1.png",
                                            "../resources/img/ghosts/orange_ghost_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/orange_ghost_W1.png",
                                            "../resources/img/ghosts/orange_ghost_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/orange_ghost_E1.png",
                                            "../resources/img/ghosts/orange_ghost_E2.png"
                                    }
                            }})));

    addStationaryGameObject(
            std::make_shared<VoidWarp>(TextureManager::loadTexture("../resources/img/red.jpg"), 60, 60, -80, 450, 2,
                                       0));
    addStationaryGameObject(
            (
                    std::make_shared<VoidWarp>(TextureManager::loadTexture("../resources/img/red.jpg"), 60, 60, 950,
                                               450, 2,
                                               1)));

    addMap(std::make_shared<Map>());


}

void Game::resetRound() {

    std::cout << "Reset round" << std::endl;
    getPlayer()->reset();

    for (auto const &ghost : getMovableGameObjects()) {
        ghost->m_positionRectangle.x = 30 * 15;
        ghost->m_positionRectangle.y = 30 * 15;
        dynamic_cast<Ghost *>(ghost.get())->powerPelletState = false;
    }
    SDL_Delay(1500);
}

void Game::gameOver() {
    std::cout << "Game over" << std::endl;

    getMap(1)->redrawPelletsOnMap();
    resetRound();
    getPlayer()->lives = 2;

}

std::vector<std::shared_ptr<Map>> &Game::getMaps() {
    return getInstance().maps;
}

void Game::beginRound() {

}


