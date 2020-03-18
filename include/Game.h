#ifndef GAME_H
#define GAME_H



#include <vector>
#include "GameObject.h"

#include <SDL.h>
#include <SDL_image.h>



class Game {
public:
    Game();

    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    static SDL_Texture *loadTexture(const char *fileName);

    std::vector<GameObject> gameObjects;

    void update();

    void render();

    void clean();

    bool running() {
        return isRunning;
    }

    static SDL_Renderer *renderer;

private:
    int cnt = 0;
    bool isRunning;
    SDL_Window *window;


};


#endif
