#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include "Map.h"
#include "GameObject.h"
#include <memory>
#include <iostream>
#include <algorithm>



class Game {
public:
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    static Game &getInstance() {
        static Game instance;
        return instance;
    }

    void update();

    void render();

    void clean();

    bool running() {
        return isRunning;
    }

    static SDL_Renderer *renderer;

    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::vector<std::shared_ptr<Map>> maps;

    static std::vector<std::shared_ptr<GameObject>> &getGameObjects();

    static std::vector<std::shared_ptr<Map>> &getMaps();

    static void addGameObject(const std::shared_ptr<GameObject> &object);

    static void addMap(const std::shared_ptr<Map> &map);


private:
    Game() = default;
    bool isRunning;
    SDL_Window *window;
    int frameCount = 0;
};

#endif
