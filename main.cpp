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

    while (true) {

        game.renderStartScreen();
        while (true) {
            if (!IM.KeyStillUp(SDL_SCANCODE_SPACE)) {
                break;
            } else if (!IM.KeyStillUp(SDL_SCANCODE_Q)) {
                abort();
            }
            IM.update();
        }

        game.startGame();
        while (GameManager::isRunning()) {
            frameStart = SDL_GetTicks();
            IM.update();
            game.update();
            if(GameManager::isRunning()) {
                game.render();
            }
            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }


    game.clean();


    return 0;
}


#pragma clang diagnostic pop