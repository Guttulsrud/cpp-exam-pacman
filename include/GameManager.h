#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include "Map.h"
#include "GameObject.h"
#include "Player.h"
#include "Stationary.h"
#include "../utils/SDL_FontCache.h"
#include <memory>
#include <iostream>
#include <algorithm>

class GameManager {
public:

    int init(const char *title, int xpos, int ypos, int width, int height);

    static GameManager &getInstance() {
        static GameManager instance;
        return instance;
    }

    void update();

    void render();

    void clean();

    bool running() {
        return isRunning;
    }
    std::shared_ptr<Player> m_player;
    std::vector<std::shared_ptr<Movable>> movableGameObjects;
    std::vector<std::shared_ptr<Stationary>> stationaryGameObjects;

    static SDL_Renderer *renderer;
    static std::vector<std::shared_ptr<Movable>> &getMovableGameObjects();
    static std::vector<std::shared_ptr<Stationary>> &getStationaryGameObjects();
    static std::shared_ptr<Player> &getPlayer();

    static void setPlayer(const std::shared_ptr<Player> &object);
    static void setGameObjects();
    static void addMovableGameObject(const std::shared_ptr<Movable> &object);
    static void addStationaryGameObject(const std::shared_ptr<Stationary> &object);
    void setMap(int map);
    int activeMap = 2;
    std::map<int, std::shared_ptr<Map>> maps;
    void resetRound();
    void startGame();
    void gameOver();
    void drawText(const char * text, float x, float y, int parameter = 0);
    void initFont(int size);
    void initFonts();
    void mapCompleted();
    void renderStartScreen();

    bool pelletsAreRemaining();
private:
    GameManager() = default;
    FC_Font* font;
    bool isRunning;
    SDL_Window *window;
};

#endif
