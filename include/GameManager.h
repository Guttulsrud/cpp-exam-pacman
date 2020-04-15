#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include "Map.h"
#include "GameObject.h"
#include "Player.h"
#include "Stationary.h"
#include "../utils/SDL_FontCache.h"
#include "Pellet.h"
#include "Ghost.h"
#include "InputManager.h"
#include <memory>
#include <iostream>
#include <algorithm>

class GameManager {
public:


    void resetRound();

    void startGame();

    void gameOver();

    void drawText(const char *text, float x, float y, int parameter = 0);

    void initFont(int size);

    void initFonts();

    void mapCompleted();

    void calculateAndDelayFrameTime();
    void run();
    static void addStationary(const std::shared_ptr<Stationary> &s);
    static void addPellet(const std::shared_ptr<Pellet> &p);
    static void addGhost(const std::shared_ptr<Ghost> &s);

    static std::shared_ptr<Player> &getPlayer();

    static SDL_Renderer *renderer;

    static std::vector<std::shared_ptr<Stationary>> &getStationery();
    static std::vector<std::shared_ptr<Pellet>> &getPellets();
    static std::vector<std::shared_ptr<Ghost>> &getGhosts();

    void update();

    void render();
    static void renderGameObjects();

    void checkForRemainingPelletsAndRemove();
    void clean();

    static bool &isRunning() {
        return getInstance().running;
    }

    static bool &isInGame() {
        return getInstance().inGame;
    }

    static GameManager &getInstance() {
        static GameManager instance;
        return instance;
    }
    bool running;
    bool inGame;

private:
    GameManager() = default;
    int init(const char *title, int x, int y, int w, int h);
    void renderStartScreen();

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart = 0;
    Uint32 frameTime;
    std::shared_ptr<Player> m_player;
    SDL_Texture *numberOfLivesDisplayTexture;
    FC_Font *font;
    SDL_Window *window;
    int currentLevel = 0;
    InputManager inputManager = InputManager::getInstance();


    static void setPlayer(const std::shared_ptr<Player> &p);

    static void addMovables();

    void setMap(const int &mapIndex);

    void renderTopDisplay();

    std::vector<std::shared_ptr<Stationary>> stationery;
    std::vector<std::shared_ptr<Pellet>> pellets;
    std::vector<std::shared_ptr<Ghost>> ghosts;
    std::shared_ptr<Map> map;
    std::vector<std::string> levelPaths = {
            "../resources/maps/level_one.txt",
            "../resources/maps/level_two.txt",
            "../resources/maps/level_three.txt"
    };

};

#endif
