#include "include/Game.h"
#include "include/InputManager.h"


#include <SDL2/SDL_ttf.h>



int main(int argc, char *argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    Uint32 frameTime;
    Game game = Game::getInstance();
    InputManager IM = InputManager::getInstance();

    game.init("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 930, 1020, false);

//    game.renderStartScreen();


    //Todo: place intro screen here: When user clicks Play, code below follows:
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