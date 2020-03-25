#ifndef GAME_H
#define GAME_H


#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <memory>


class Game {
public:
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    static Game &getInstance(){
        static Game instance;
        return instance;
    }

    static SDL_Texture *loadTexture(const char *fileName);

    void update();

    void render();

    void clean();

    bool running() {
        return isRunning;
    }
    static SDL_Renderer *renderer;

private:
    Game() = default;
    bool isRunning;
    SDL_Window *window;
};


#endif
