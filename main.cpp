#include <iostream>
#include "include/Game.h"


//TODO: Make include headerfile which fixes crossplattform SDL dependencies

Game *game = nullptr;

int main(int argc, char *argv[]) {


    game = new Game();
    game->init("Halla", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    //TODO: Make wrapper class "fascade" for SDL2?
    // Har egne metoder som forenkler kall til de wrappede undermetodene (gjerne flere om gangen).
    // Hvis undermetodene tilhører klasser, blir disse klassene private medlemsvariabler i Facade klassen.



}

