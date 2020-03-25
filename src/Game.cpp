
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/GameObject.h"
#include "../include/Player.h"
#include "../include/Map.h"
#include "../include/WallEntity.h"
#include <iostream>

SDL_Renderer *Game::renderer = nullptr;
Map * map = nullptr;
void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

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

    addGameObject(std::make_shared<Player>("../resources/img/pacman-open.png", 40, 40, 55, 55, 0, 3));

    map = new Map();

//
//    addGameObject(std::make_shared<WallEntity>("../resources/img/wall.png", 800, 50, 0, -50, 1));
//    addGameObject(std::make_shared<WallEntity>("../resources/img/wall.png", 800, 50, 0, 800, 2));
//    addGameObject(std::make_shared<WallEntity>("../resources/img/wall.png", 50, 800, -50, 0, 2));
//    addGameObject(std::make_shared<WallEntity>("../resources/img/wall.png", 50, 800, 800, 0, 2));

}

void Game::render() {
    SDL_RenderClear(renderer);

//    std::for_each(std::begin(Game::getGameObjects()), std::end(Game::getGameObjects()),
//                  [](std::shared_ptr<GameObject> &object) {
//                      object->render();
//                  });

//    Map map = Map::getInstance();
//    map.drawMap();
//    std::vector<SDL_Rect> walls = Map::getWalls();

    map->drawMap();

    getGameObjects()[0]->render();
//    getGameObjects()[1]->render();


    SDL_RenderPresent(renderer);
}

Game::~Game() {

}

void Game::addGameObject(std::shared_ptr<GameObject> const &o) {
    getGameObjects().emplace_back(o);
}

void Game::update() {
//    std::for_each(std::begin(Game::getGameObjects()), std::end(Game::getGameObjects()),
//                  [](std::shared_ptr<GameObject> &object) {
//                      object->update();
//                  });
    getGameObjects()[0]->update();
//    getGameObjects()[1]->update();
}

void Game::clean() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned.." << std::endl;
}

SDL_Texture *Game::loadTexture(const char *texture) {

    SDL_Surface *surface = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    return tex;
}


