#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>



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










int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
    SDL_Window *window = nullptr; // Pointer to Window

    window = SDL_CreateWindow(
            "Testing",          //    window title
            SDL_WINDOWPOS_UNDEFINED,           //    initial x position
            SDL_WINDOWPOS_UNDEFINED,           //    initial y position
            550,                               //    width, in pixels
            400,                               //    height, in pixels
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL //    flags
    );


    if (window == nullptr) {
        std::cerr << "Failed to create window: "
                  << SDL_GetError() << std::endl;
        SDL_Quit(); // Rydd opp!
        return EXIT_FAILURE;
    }

    SDL_Delay(5000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;


}