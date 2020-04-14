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

    int init(const char *title, int x, int y, int w, int h);

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
    std::vector<std::shared_ptr<Movable>> movables;
    std::vector<std::shared_ptr<Stationary>> stationery;

    static SDL_Renderer *renderer;

    static std::vector<std::shared_ptr<Movable>> &getMovables();

    static std::vector<std::shared_ptr<Stationary>> &getStationery();

    static std::shared_ptr<Player> &getPlayer();

    static int &getCurrentLevel();

    static void setPlayer(const std::shared_ptr<Player> &p);

    static void setCurrentLevel(const int &currentLevel);

    static void addMovables();

    static void addMovable(const std::shared_ptr<Movable> &m);

    static void addStationary(const std::shared_ptr<Stationary> &s);

    void setMap(const int &mapIndex);

    int currentLevel = 0;
    std::shared_ptr<Map> map;

    void resetRound();

    void startGame();

    void gameOver();

    void drawText(const char *text, float x, float y, int parameter = 0);

    void initFont(int size);

    void initFonts();

    void mapCompleted();

    void renderStartScreen();
    void renderTopDisplay();

    bool pelletsAreRemaining();

private:
    GameManager() = default;

    SDL_Texture* liveCountTexture;
    FC_Font *font;
    bool isRunning;
    SDL_Window *window;
};

#endif
