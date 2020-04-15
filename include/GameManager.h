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
    static SDL_Renderer *m_renderer;

    std::vector<std::string> levelPaths = {
            "../resources/maps/level_one.txt",
            "../resources/maps/level_two.txt",
            "../resources/maps/level_three.txt"
    };

    static GameManager &getInstance() {
        static GameManager instance;
        return instance;
    }

    void run();
    void render();
    void gameOver();
    void resetRound();

    static std::shared_ptr<Player> &getPlayer();
    static std::vector<std::shared_ptr<Stationary>> &getStationery();
    static std::vector<std::shared_ptr<Pellet>> &getPellets();
    static std::vector<std::shared_ptr<Ghost>> &getGhosts();

    static void addStationary(const std::shared_ptr<Stationary> &s);
    static void addPellet(const std::shared_ptr<Pellet> &p);

private:

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    int currentLevel = 0;
    bool running;
    bool inGame;

    SDL_Texture *numberOfLivesDisplayTexture;
    FC_Font *font;
    SDL_Window *window;

    InputManager inputManager = InputManager::getInstance();

    std::shared_ptr<Player> m_player;
    std::vector<std::shared_ptr<Stationary>> stationery;
    std::vector<std::shared_ptr<Pellet>> pellets;
    std::vector<std::shared_ptr<Ghost>> ghosts;
    std::shared_ptr<Map> map;

    GameManager() = default;
    int init(const char *title, int x, int y, int w, int h);

    void startGame();
    void update();
    void clean();
    void mapCompleted();
    void addMovables();
    void checkForRemainingPelletsAndRemove();

    void initFonts();
    void setFontSize(int size);
    void drawText(const char *text, float x, float y, int parameter = 0);

    void renderGameObjects();
    void renderTopDisplay();
    void renderStartScreen();

    void addGhost(const std::shared_ptr<Ghost> &s);
    void setPlayer(const std::shared_ptr<Player> &p);
    void setMap(const int &mapIndex);

    Uint32 frameTime;
    Uint32 frameStart = 0;
    void calculateAndDelayFrameTime();
};

#endif