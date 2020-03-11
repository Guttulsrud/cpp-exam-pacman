#include <iostream>
#include "include/Game.h"


// -------- Input management: ---------- //


// -------- EVENT PUMP ---------- //
// Bruker event pump på events som:
// ikke skal kombinere inputs.
// ikke skal sjekkes flere steder i koden.
// ikke skal ha varighet.
// ikke må glemmes

//        Eksempler:
// Exit to main menu,
// Main menu tasks,
// Item clicks, …

// -------- STATE SNAPSHOT ---------- //
// Bruker state sjekking på resten (movement, actions). (State snapshot)




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

