//
// Created by Håkon on 25.03.2020.
//


#include <iostream>
#include "../include/Map.h"
#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/Pellet.h"
#include "../include/WallEntity.h"


int levelOne[32][32] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 0, 0, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 0, 2, 1},
        {1, 0, 5, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 0, 3, 1},
        {1, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 1},
        {1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 0, 2, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 0, 2, 1},
        {1, 0, 2, 0, 0, 0, 0, 2, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 2, 0, 0, 0, 0, 2, 1},
        {1, 0, 2, 2, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 0, 2, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 1, 0, 2, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 2, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 2, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 0, 0, 0, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 1, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 0, 2, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 2, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 2, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        {1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 0, 2, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 0, 2, 1},
        {1, 0, 5, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 4, 1},
        {1, 0, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 2, 2, 2, 1},
        {1, 1, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 1, 1},
        {1, 0, 0, 0, 2, 0, 0, 2, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 2, 0, 0, 2, 0, 0, 1},
        {1, 0, 2, 2, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 1},
        {1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1},
        {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
        {1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


Map::Map() {
    wall = TextureManager::loadTexture("../resources/img/blue.png");
    pellet = TextureManager::loadTexture("../resources/img/pellet.png");
    pelletLarge = TextureManager::loadTexture("../resources/img/pellet_large.png");
    loadLevelMap(levelOne);
}


void Map::loadLevelMap(int array[32][32]) {
    int tileType = 0;
    int idIncrementer = 0;

    for (int column = 0; column < 32; column++) {
        for (int row = 0; row < 32; row++) {

            tileType = array[column][row];
            idIncrementer++;
            switch (tileType) {
                case 1:
                    Game::addGameObject(std::make_shared<WallEntity>(wall, 25, 25, row * 25, column * 25, idIncrementer));
                    break;
                case 2:
                    Game::addGameObject(std::make_shared<Pellet>(pellet, 5, 5, row * 24.9, column * 25, idIncrementer));
                    break;
                case 3:
                    Game::addGameObject(std::make_shared<Pellet>(pelletLarge, 15, 15, row * 24.73, column * 23.9, idIncrementer));
                    break;
                case 4:
                    Game::addGameObject(std::make_shared<Pellet>(pelletLarge, 15, 15, row * 24.73, column * 24.8, idIncrementer));
                    break;
                case 5:
                    Game::addGameObject(std::make_shared<Pellet>(pelletLarge, 15, 15, row * 22, column * 24.8, idIncrementer));
                    break;
                default:;
                //todo: Consider different approach to large pellet positions. Will be different on other maps
            }
        }
    }
}


Map::~Map() {

}