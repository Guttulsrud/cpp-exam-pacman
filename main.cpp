#include <iostream>
#include "include/Game.h"
#include "include/InputManager.h"

int main(int argc, char *argv[]) {


    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    Uint32 frameTime;

    Game game = Game::getInstance();
    game.init("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 800, false);

    while (game.running()) {

        frameStart = SDL_GetTicks();
        InputManager::getInstance().update();
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