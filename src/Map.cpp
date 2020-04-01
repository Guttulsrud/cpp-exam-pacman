//
// Created by Håkon on 25.03.2020.
//


#include <iostream>
#include "../include/Map.h"
#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/Pellet.h"
#include "../include/WallEntity.h"
//std::array


//logic map
int levelOne[32][30] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 0, 0, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 0, 2, 1},
        {1, 0, 0, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 0, 2, 1},
        {1, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 1},
        {1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 0, 0, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 0, 2, 1},
        {1, 0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 2, 0, 0, 0, 0, 2, 1},
        {1, 0, 0, 0, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 1},
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
        {1, 0, 2, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 2, 1},
        {1, 0, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 2, 2, 2, 1},
        {1, 1, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 1, 1},
        {1, 0, 0, 0, 2, 0, 0, 2, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 2, 0, 0, 2, 0, 0, 1},
        {1, 0, 2, 2, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 1},
        {1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1},
        {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
        {1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

//pixel map



Map::Map() {
//    m_wall = Game::loadTexture("../resources/img/blue.png");
//    m_nonWall = Game::loadTexture("../resources/img/black.png");
//    m_pellet = Game::loadTexture("../resources/img/pellet.png");


    loadLevelMap(levelOne);

    m_sourceRectangle.x = m_sourceRectangle.y = 0;
    m_sourceRectangle.w = m_destinationRectangle.w = 25;
    m_sourceRectangle.h = m_destinationRectangle.h = 25;

    m_destinationRectangle.x = m_destinationRectangle.y = 0;


}

void Map::loadLevelMap(int array[32][30]) {
    int tileType = 0;


    SDL_Texture* wall = Game::loadTexture("../resources/img/blue.png");
    SDL_Texture* pellet = Game::loadTexture("../resources/img/pellet.png");


    for (int column = 0; column < 32; column++) {
        for (int row = 0; row < 30; row++) {

            tileType = array[column][row];


            if (tileType == 1) {
                Game::addGameObject(std::make_shared<WallEntity>(wall, 25, 25, row*25, column*25, 1));

            } else if (tileType == 2) {
                Game::addGameObject(std::make_shared<Pellet>(pellet, 5, 5, row*25, column*25, 1));

            } else {

            }
        }
    }
}



void Map::drawMap() {


//    for (auto &object : Game::getGameObjects()) {
//        TextureManager::draw(object.get()->texture, object.get()->m_sourceRectangle, object.get()->m_positionRectangle);
//    }


//    int tileType = 0;
//
//    for (int row = 0; row < 32; row++) {
//        for (int column = 0; column < 30; column++) {
//            tileType = map[row][column];
//
//            m_destinationRectangle.x = column * 25;
//            m_destinationRectangle.y = row * 25;
//
//
//            if (tileType == 1) {
//
//                TextureManager::draw(m_wall, m_sourceRectangle, m_destinationRectangle);
//            } else if (tileType == 2) {
//
//                m_destinationRectangle.w = 5;
//                m_destinationRectangle.h = 5;
//                TextureManager::draw(m_pellet, m_sourceRectangle, m_destinationRectangle);
//                m_destinationRectangle.w = 25;
//                m_destinationRectangle.h = 25;
//
//            } else {
//                TextureManager::draw(m_nonWall, m_sourceRectangle, m_destinationRectangle);
//            }
//
//        }
//    }
}


#include "../include/Map.h"
