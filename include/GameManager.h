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

    static GameManager &getInstance() {
        static GameManager instance;
        return instance;
    }

    void run();

    void render();

    void gameOver();

    void startNewRound();

    int readHighScoreFromFile();

    static std::shared_ptr<Player> &getPlayer();

    static std::vector<std::shared_ptr<Stationary>> &getStationery();

    static std::vector<std::shared_ptr<Pellet>> &getPellets();

    static std::vector<std::shared_ptr<Ghost>> &getGhosts();

    static void addStationary(const std::shared_ptr<Stationary> &s);

    static void addPellet(const std::shared_ptr<Pellet> &p);

    static void addGhost(const std::shared_ptr<Ghost> &s);

    static void writeHighScore(int score);

    int m_currentScore = 0;
    int m_scoreLastRound = 0;
    int m_highScore = 0;
    int m_newHighScore = 0;
    int m_lives = 3;

    std::vector<std::string> m_levelPaths = {
            "../resources/maps/level_one.txt",
            "../resources/maps/level_two.txt",
            "../resources/maps/level_three.txt"
    };

private:
    void update();

    void startGame();

    void runGameLoop();

    void waitForMenuInput();

    void updateMovables();

    void mapCompleted();

    void createMovables();

    void checkIfMapComplete();

    void calculateAndDelayFrameTime();

    void handleCollisions();

    void checkForPlayerAndGhost();

    void renderGameObjects();

    void renderTopDisplay();

    void setMap(const int &mapIndex);

    void playerDead();

    void ghostDead(std::shared_ptr<Ghost> &ghost);

    GameManager() = default;


    const int FPS = 60;
    int currentLevel = 0;
    bool running = true;
    bool inGame = true;
    const int frameDelay = 1000 / FPS;

    Uint32 m_frameTime;
    Uint32 m_frameStart = 0;
    InputManager inputManager = InputManager::getInstance();
    SDLManager sdlManager = SDLManager::getInstance();
    SDL_Texture *numberOfLivesDisplayTexture;
    std::shared_ptr<Player> m_player;
    std::vector<std::shared_ptr<Stationary>> m_stationery;
    std::vector<std::shared_ptr<Pellet>> m_pellets;
    std::vector<std::shared_ptr<Ghost>> m_ghosts;
    std::shared_ptr<Map> m_map;
};

#endif