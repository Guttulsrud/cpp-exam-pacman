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
#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/GameManager.h"
#include "../include/Pellet.h"
#include "../include/Ghost.h"
#include <SDL_mixer.h>
#include <future>
#include <fstream>


enum Sound {
    EAT_PELLET, EAT_POWER_PELLET, DEATH, EAT_FRUIT, EAT_GHOST, INTRO, MAP_COMPLETED, GHOST_RETURN
};

class GameManager {
public:

    std::map<Sound, Mix_Chunk *> sounds = {{EAT_PELLET,       Mix_LoadWAV(
                                                                      "../resources/sounds/pacman/pacman_chomp.wav")},
                                           {EAT_POWER_PELLET, Mix_LoadWAV(
                                                                      "../resources/sounds/pacman/eat_powerpellet.mp3")},
                                           {EAT_FRUIT,        Mix_LoadWAV(
                                                                      "../resources/sounds/pacman/pacman_eatfruit.wav")},
                                           {EAT_GHOST,        Mix_LoadWAV(
                                                                      "../resources/sounds/pacman/pacman_eatghost.wav")},
                                           {DEATH,            Mix_LoadWAV(
                                                                      "../resources/sounds/pacman/pacman_death.wav")},
                                           {INTRO,            Mix_LoadWAV(
                                                                      "../resources/sounds/game/pacman_beginning.wav")},
                                           {MAP_COMPLETED,    Mix_LoadWAV(
                                                                      "../resources/sounds/pacman/pacman_extrapac.wav")},
                                           {GHOST_RETURN,     Mix_LoadWAV(
                                                                      "../resources/sounds/ghosts/ghost_return_to_home.mp3")},
    };
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

    int readHighScoreFromFile();

    static void writeHighScore(int score);


    static std::shared_ptr<Player> &getPlayer();

    static std::vector<std::shared_ptr<Stationary>> &getStationery();

    static std::vector<std::shared_ptr<Pellet>> &getPellets();

    static std::vector<std::shared_ptr<Ghost>> &getGhosts();

    static void addStationary(const std::shared_ptr<Stationary> &s);

    static void addPellet(const std::shared_ptr<Pellet> &p);


    int currentScore = 0;
    int scoreLastRound = 0;
    int highScore = 0;
    int newHighScore = 0;
    int lives = 3;

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

    void handleCollisions();

    void checkForPelletPickup();

    void checkForPlayerAndGhost();

    void renderGameObjects();

    void renderTopDisplay();

    void addGhost(const std::shared_ptr<Ghost> &s);

    void setMap(const int &mapIndex);

    Uint32 frameTime;
    Uint32 frameStart = 0;

    void calculateAndDelayFrameTime();

    void playSound(Sound sound, int channel);
};

#endif