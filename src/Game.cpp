
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/GameObject.h"
#include "../include/Player.h"
#include "../include/Map.h"
#include "../include/WallEntity.h"
#include "../include/Pellet.h"
#include "../include/VoidWarp.h"
#include <iostream>
#include <algorithm>

SDL_Renderer *Game::renderer = nullptr;
Map *map = nullptr;

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

    addGameObject(std::make_shared<Player>("../resources/img/pacman-open.png", 28, 28, 90, 30, 0, 3));
    map = new Map();


    for (int i = 40; i < 500; i++) {
        if (i % 40 == 0) {
            addGameObject(std::make_shared<Pellet>("../resources/img/pellet.png", 7, 7, 57, i, 1));
        }


    }

    addGameObject(std::make_shared<VoidWarp>("../resources/img/red.jpg", 28, 28, 200, 180, 2));


}

void Game::render() {
    SDL_RenderClear(renderer);
    map->drawMap();

    std::for_each(std::begin(Game::getGameObjects()), std::end(Game::getGameObjects()),
                  [](std::shared_ptr<GameObject> &object) {
                      object->render();
                  });


    SDL_RenderPresent(renderer);
}

Game::~Game() {

}

void Game::addGameObject(std::shared_ptr<GameObject> const &o) {
    getGameObjects().emplace_back(o);
}

void Game::update() {
    std::for_each(std::begin(Game::getGameObjects()), std::end(Game::getGameObjects()),
                  [](std::shared_ptr<GameObject> &object) {
                      object->update();
                  });

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


