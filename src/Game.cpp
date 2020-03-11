
#include "../include/Game.h"
#include "../include/InputManager.h"
#include <iostream>

SDL_Texture *playerTexture;
SDL_Rect srcR, destR;

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
            SDL_SetRenderDrawColor(renderer, 200, 50, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
    }

    playerTexture = loadTexture("../Resources/img/player.png", renderer);
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTexture, NULL, &destR);
    SDL_RenderPresent(renderer);
}


Game::Game() {
//    SDL_Event event;
//    SDL_PollEvent(&event);
//    switch (event.type) {
//        case SDL_QUIT:
//            isRunning = false;
//            break;
//
//        default:
//            break;
//    }

}

Game::~Game() {

}


void Game::update() {

    if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_W)) {
        destR.y -= 3;
    }
    if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_A)) {
        destR.x -= 3;
    }
    if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_S)) {
        destR.y += 3;
    }
    if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_D)) {
        destR.x += 3;
    }


    destR.h = 64;
    destR.w = 64;


}

void Game::clean() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned.." << std::endl;
}

SDL_Texture *Game::loadTexture(const char *fileName, SDL_Renderer *renderer) {

    SDL_Surface *surface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}


