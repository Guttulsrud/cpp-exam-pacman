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
    }


    setPlayer(std::make_shared<Player>(TextureManager::loadTexture("../resources/img/pacman/base.png"),
                                       120, 60, 0, 3));
    ///TODO: Draw with map class
    addGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/green_ghost_E1.png"),
            60, 60, 0, 2));
    addGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/orange_ghost_E1.png"),
            120, 60, 0, 2));
    addGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/red_ghost_E1.png"),
            180, 60, 0, 2));
    addGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/purple_ghost_E1.png"),
            240, 60, 0, 2));

    addGameObject(
            std::make_shared<VoidWarp>(TextureManager::loadTexture("../resources/img/red.jpg"), 60, 60, -80, 450, 2,
                                       0));
    addGameObject(
            std::make_shared<VoidWarp>(TextureManager::loadTexture("../resources/img/red.jpg"), 60, 60, 950, 450, 2,
                                       1));

    addMap(std::make_shared<Map>());

}


void removeGameObjects(std::vector<std::shared_ptr<GameObject>> &objects) {

    objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                           [](const std::shared_ptr<GameObject> &pellet) {
                               return pellet->getType() == PELLET && dynamic_cast<Pellet *>(pellet.get())->eaten;
                           }),
            objects.end());
}


void Game::update() {
    frameCount++;
    std::vector<std::shared_ptr<GameObject>> &objects = Game::getGameObjects();
    std::shared_ptr<Player> &player = Game::getPlayer();

    if (frameCount > 5) {
        player->m_texture = player->base;
    }
    if (frameCount > 10) {
        player->setPlayerAnimationDirectionMedium();
    }
    if (frameCount > 15) {
        player->setPlayerAnimationDirectionLarge();
    }
    if (frameCount > 20) {
        player->setPlayerAnimationDirectionMedium();
        frameCount = 0;
    }


//    for (auto &gameObject : objects) {
//        gameObject->update();
//    }
    player->update();

    removeGameObjects(objects);


}


void Game::render() {

    SDL_RenderClear(renderer);
    for (auto &gameObject : Game::getGameObjects()) {
        gameObject->render();
    }


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
