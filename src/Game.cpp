#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Ghost.h"
#include "../include/VoidWarp.h"
#include "../include/Pellet.h"

#include <SDL2/SDL.h>

SDL_Renderer *Game::renderer = nullptr;


void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    }
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {


        std::cout << "Initializing.." << std::endl;
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, flags);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
        setUpGameObjects();
    }
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

    for (auto &m : movables) {
        m->update();
    }


    removeEatenPellets(Game::getStationaryGameObjects());
}


void Game::render() {
    SDL_RenderClear(renderer);
    std::vector<std::shared_ptr<MovableObject>> &movables = Game::getMovableGameObjects();
    std::vector<std::shared_ptr<StationaryObject>> &stationary = Game::getStationaryGameObjects();
    std::shared_ptr<Player> &player = Game::getPlayer();


    for (auto &m :movables) {
        m->render();
    }
    for (auto &s : stationary) {
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

void Game::addGameObject(std::shared_ptr<GameObject> const &object) {
    getGameObjects().emplace_back(object);
}

void Game::setPlayer(std::shared_ptr<Player> const &object) {
    getInstance().m_player = object;
}


std::vector<std::shared_ptr<Map>> &Game::getMaps() {
    return getInstance().maps;
}

std::vector<std::shared_ptr<GameObject>> &Game::getGameObjects() {
    return getInstance().gameObjects;
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

void Game::setUpGameObjects() {

    setPlayer(std::make_shared<Player>(TextureManager::loadTexture("../resources/img/pacman/base.png"),
                                       440, 540, 0, 2));
    //TODO: Draw with map class
    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/green_ghost_E1.png"),
            440, 450, 0, 2));

    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/orange_ghost_E1.png"),
            440, 450, 0, 2));

    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/red_ghost_E1.png"),
            440, 450, 0, 2));

    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/purple_ghost_E1.png"),
            440, 450, 0, 2));

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


