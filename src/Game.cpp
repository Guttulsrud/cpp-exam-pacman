#include "../include/Game.h"
#include <SDL2/SDL.h>
#include <iostream>

void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
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
    } else {
        isRunning = false;
    }
}

Game::Game() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }

}

Game::~Game() {

}

void Game::handleEvents() {

}

void Game::render() {
    SDL_RenderClear(renderer);

    // Add render stuff here


    SDL_RenderPresent(renderer);

}

void Game::update() {
    cnt++;
    std::cout << cnt << std::endl;
}

void Game::clean() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned.." << std::endl;
}
