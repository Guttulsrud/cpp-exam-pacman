#ifndef GAME_H
#define GAME_H


#ifdef WIN32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>

#endif

class Game {
public:
    Game();

    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    static SDL_Texture *loadTexture(const char *fileName, SDL_Renderer *renderer);

    void update();

    void render();

    void clean();

    bool running() {
        return isRunning;
    }

private:
    int cnt = 0;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;


};


#endif
