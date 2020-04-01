
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/GameObject.h"
#include "../include/Player.h"
#include "../include/Map.h"
#include "../include/TextureManager.h"
#include <iostream>

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

    SDL_Texture *playerTex = TextureManager::loadTexture("../resources/img/pacman-open.png");

    addGameObject(std::make_shared<Player>(playerTex, 48, 48, 60, 25, 0, 3));
    addMap(std::make_shared<Map>());
}

void Game::render() {
    SDL_RenderClear(renderer);

    for (auto &gameObject : Game::getGameObjects()) {
        gameObject->render();
    }

    SDL_RenderPresent(renderer);
}

void Game::update() {
    for (auto &gameObject : Game::getGameObjects()) {
        gameObject->update();
    }
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

std::vector<std::shared_ptr<Map>> &Game::getMaps() {
    return getInstance().maps;
}

std::vector<std::shared_ptr<GameObject>> &Game::getGameObjects() {
    return getInstance().gameObjects;
}

Game::~Game() {

}
