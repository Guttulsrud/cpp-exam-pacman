
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/GameObject.h"
#include "../include/Player.h"
#include "../include/Map.h"
#include "../include/WallEntity.h"
#include "../include/Pellet.h"
#include "../include/TextureManager.h"
#include <iostream>

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

    SDL_Texture *playerTex = TextureManager::loadTexture("../resources/img/pacman-closed.png");
    addGameObject(std::make_shared<Player>(playerTex, 50, 50, 338, 425 , 0, 1));
    map = new Map();


//    for (int i = 40; i < 270; i++) {
//        if (i % 40 == 0) {
//            addGameObject(std::make_shared<Pellet>("../resources/img/pellet.png", 7, 7, 48, i, 1));
//        }
//    }

}

void Game::render() {
    SDL_RenderClear(renderer);
    map->drawMap();

    for (auto &object : Game::getGameObjects()) {
        object->render();
    }


    SDL_RenderPresent(renderer);
}

Game::~Game() {

}

void Game::addGameObject(std::shared_ptr<GameObject> const &o) {
    getGameObjects().emplace_back(o);
}


void Game::update() {

    Game::getGameObjects()[0]->update();

    for (auto &object : Game::getGameObjects()) {
        object->update();
    }
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


