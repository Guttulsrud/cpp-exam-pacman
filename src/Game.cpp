
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/GameObject.h"
#include <iostream>

SDL_Renderer *Game::renderer = nullptr;

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
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
    }
    addGameObject(std::make_shared<GameObject>("../resources/img/player.png", 30, 30, 250, 250, 0));
    addGameObject(std::make_shared<GameObject>("../resources/img/player.png", 30, 30, 50, 50, 1, true));
    addGameObject(std::make_shared<GameObject>("../resources/img/player.png", 600, 10, 0, 0, 2, true));
    addGameObject(std::make_shared<GameObject>("../resources/img/player.png", 600, 10, 0, 500, 2, true));
    addGameObject(std::make_shared<GameObject>("../resources/img/player.png", 10, 500, 0, 0, 2, true));
    addGameObject(std::make_shared<GameObject>("../resources/img/player.png", 10, 500, 600, 0, 2, true));
    addGameObject(std::make_shared<GameObject>("../resources/img/player.png", 10, 250, 300, 0, 2, true));

}

void Game::render() {
    SDL_RenderClear(renderer);

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
                      if(object->m_id == 1){
                          object->moveSpeed = 1;
                          object->setDestination(Game::getGameObjects()[0]->m_position.x,Game::getGameObjects()[0]->m_position.y);
                      }
                      if(object->m_id == 0)
                          object->moveSpeed = 7;
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


