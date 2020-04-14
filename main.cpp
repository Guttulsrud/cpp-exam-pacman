#include "include/GameManager.h"
#include "include/InputManager.h"


#include <SDL2/SDL_ttf.h>



int main(int argc, char *argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    Uint32 frameTime;
    GameManager game = GameManager::getInstance();
    InputManager IM = InputManager::getInstance();

    game.init("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 930, 1020);

    game.renderStartScreen();

    game.startGame();

    while (game.running()) {
        frameStart = SDL_GetTicks();
        IM.update();
        game.update();
        game.render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game.clean();


    return 0;
}


#pragma clang diagnostic pop