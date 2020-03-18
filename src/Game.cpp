
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/GameObject.h"
#include <iostream>

GameObject *player;
GameObject *enemy;
GameObject *enemy2;
SDL_Renderer* Game::renderer = nullptr;

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

    player = new GameObject("../resources/img/player.png", 0, 0, 1, false);
    enemy = new GameObject("../resources/img/player.png", 600, 600, 2, true);
    enemy2 = new GameObject("../resources/img/player.png", 600, 600, 3, true);

    enemy2->moveSpeed = 2;
    enemy->moveSpeed = 3;
    Game::gameObjects.emplace_back(*player);
    Game::gameObjects.emplace_back(*enemy);
    Game::gameObjects.emplace_back(*enemy2);
}

void Game::render() {
    SDL_RenderClear(renderer);
    player->render();
    enemy->render();
    enemy2->render();
    SDL_RenderPresent(renderer);
}


Game::Game() {

}

Game::~Game() {

}


void Game::update() {
    player->update(gameObjects);
    enemy->setDestination(player->m_position.x, player->m_position.y);
    enemy2->setDestination(enemy->m_position.x, enemy->m_position.y);
    enemy->update(gameObjects);
    enemy2->update(gameObjects);

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



