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

    void startNewRound();

    void stopSoundOnChannel(int channel);

    void stopExecutionWhileSoundPlaying(int channel);

    int readHighScoreFromFile();

    static void writeHighScore(int score);


    static std::shared_ptr<Player> &getPlayer();
    static std::vector<std::shared_ptr<Stationary>> &getStationery();
    static std::vector<std::shared_ptr<Pellet>> &getPellets();
    static std::vector<std::shared_ptr<Ghost>> &getGhosts();

    static void addStationary(const std::shared_ptr<Stationary> &s);
    static void addPellet(const std::shared_ptr<Pellet> &p);
    static void addGhost(const std::shared_ptr<Ghost> &s);


    int m_currentScore = 0;
    int m_scoreLastRound = 0;
    int m_highScore = 0;
    int m_newHighScore = 0;
    int m_lives = 3;



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
    std::vector<std::shared_ptr<Stationary>> m_stationery;
    std::vector<std::shared_ptr<Pellet>> m_pellets;
    std::vector<std::shared_ptr<Ghost>> m_ghosts;
    std::shared_ptr<Map> m_map;

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

    void checkForPelletPickup();

    void checkForPlayerAndGhost();

    void renderGameObjects();
    void renderTopDisplay();

    void setMap(const int &mapIndex);

    Uint32 frameTime;
    Uint32 frameStart = 0;

    GameManager() = default;



};

#endif