#ifndef GAME_H
#define GAME_H

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
#include "SDLManager.h"


class GameManager {
public:
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
    bool running = true;
    bool inGame = true;

    InputManager inputManager = InputManager::getInstance();
    SDLManager sdlManager = SDLManager::getInstance();

    SDL_Texture *numberOfLivesDisplayTexture;

    std::shared_ptr<Player> m_player;
    std::vector<std::shared_ptr<Stationary>> stationery;
    std::vector<std::shared_ptr<Pellet>> pellets;
    std::vector<std::shared_ptr<Ghost>> ghosts;
    std::shared_ptr<Map> map;

    GameManager() = default;

    void startGame();
    void update();
    void mapCompleted();
    void createMovables();
    void checkForRemainingPelletsAndRemove();

    void renderGameObjects();
    void renderTopDisplay();

    void addGhost(const std::shared_ptr<Ghost> &s);
    void setMap(const int &mapIndex);

    Uint32 frameTime;
    Uint32 frameStart = 0;
    void calculateAndDelayFrameTime();
};

#endif