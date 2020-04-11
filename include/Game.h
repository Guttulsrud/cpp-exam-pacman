#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include "Map.h"
#include "GameObject.h"
#include "Player.h"
#include "StationaryObject.h"
#include "../utils/SDL_FontCache.h"
#include <memory>
#include <iostream>
#include <algorithm>


class Game {
public:
    ~Game();

    int init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

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



    std::shared_ptr<Player> m_player;
    std::vector<std::shared_ptr<MovableObject>> movableGameObjects;
    std::vector<std::shared_ptr<StationaryObject>> stationaryGameObjects;
    std::vector<std::shared_ptr<Map>> maps;

    static std::vector<std::shared_ptr<MovableObject>> &getMovableGameObjects();
    static std::vector<std::shared_ptr<StationaryObject>> &getStationaryGameObjects();
    static std::vector<std::shared_ptr<Map>> &getMaps();
    static std::shared_ptr<Map> &getMap(int levelNumber);
    static std::shared_ptr<Player> &getPlayer();

    static void setPlayer(const std::shared_ptr<Player> &object);
    static void setGameObjects();
    static void addMovableGameObject(const std::shared_ptr<MovableObject> &object);
    static void addStationaryGameObject(const std::shared_ptr<StationaryObject> &object);
    static void addMap(const std::shared_ptr<Map> &map);
    static void resetRound();
    static void newGame();

    static void gameOver();
    static void beginRound();
    void renderHighScore();


private:
    Game() = default;
    FC_Font* font;
    bool isRunning;
    SDL_Window *window;
    int frameCount = 0;

};

#endif
