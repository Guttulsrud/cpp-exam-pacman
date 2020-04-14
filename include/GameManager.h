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

    void resetRound();

    void startGame();

    void gameOver();

    void drawText(const char *text, float x, float y, int parameter = 0);

    void initFont(int size);

    void initFonts();

    void mapCompleted();

    void renderStartScreen();

    static void addStationary(const std::shared_ptr<Stationary> &s);

    static std::shared_ptr<Player> &getPlayer();

    static SDL_Renderer *renderer;

    static std::vector<std::shared_ptr<Movable>> &getMovables();

    static std::vector<std::shared_ptr<Stationary>> &getStationery();

    void update();

    void render();
    static void renderGameObjects();

    void clean();

    static bool &isRunning() {
        return getInstance().running;
    }

    static GameManager &getInstance() {
        static GameManager instance;
        return instance;
    }
    bool running;

private:
    GameManager() = default;

    std::shared_ptr<Player> m_player;
    SDL_Texture *numberOfLivesDisplayTexture;
    FC_Font *font;
    SDL_Window *window;
    int currentLevel = 0;

    static void setPlayer(const std::shared_ptr<Player> &p);

    static void addMovables();

    static void addMovable(const std::shared_ptr<Movable> &m);

    void setMap(const int &mapIndex);

    bool pelletsAreRemaining();

    void renderTopDisplay();

    std::vector<std::shared_ptr<Movable>> movables;
    std::vector<std::shared_ptr<Stationary>> stationery;
    std::shared_ptr<Map> map;
    std::vector<std::string> levelPaths = {
            "../resources/maps/level_one.txt",
            "../resources/maps/level_two.txt",
            "../resources/maps/level_three.txt"
    };

};

#endif
