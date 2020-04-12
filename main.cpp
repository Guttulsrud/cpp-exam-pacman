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

    game.init("pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 930, 1020, false);



    //Todo: place intro screen here: When user clicks Play, code below follows:
    game.newGame();
    while (Mix_Playing(1)) {
        IM.update();
    }

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

    //TODO: Make wrapper class "fascade" for SDL2?
    // Har egne metoder som forenkler kall til de wrappede undermetodene (gjerne flere om gangen).
    // Hvis undermetodene tilhører klasser, blir disse klassene private medlemsvariabler i Facade klassen.


    return 0;
}


#pragma clang diagnostic pop