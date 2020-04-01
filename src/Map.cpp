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
    m_wall = Game::loadTexture("../resources/img/blue.png");
    m_nonWall = Game::loadTexture("../resources/img/black.png");
    m_pellet = Game::loadTexture("../resources/img/pellet.png");


    loadMap(levelOne);

    m_sourceRectangle.x = m_sourceRectangle.y = 0;
    m_sourceRectangle.w = m_destinationRectangle.w = 25;
    m_sourceRectangle.h = m_destinationRectangle.h = 25;

    m_destinationRectangle.x = m_destinationRectangle.y = 0;


}

void Map::loadMap(int array[32][30]) {
    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 30; column++) {
            map2D[row][column] = array[row][column];
        }
    }
}

std::vector<SDL_Rect> Map::walls;
std::vector<SDL_Rect> Map::pellets;
std::vector<SDL_Texture *> Map::pelletsTex;
std::vector<Pellet> Map::pelletObjects;

void Map::drawMap() {
    int type = 0;
    int test = 0;


    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 30; column++) {
            type = map2D[row][column];

            m_destinationRectangle.x = column * 25;
            m_destinationRectangle.y = row * 25;

            //TODO: Rewrite method to only draw map once and not every frame. Should create game objects instead. Wall object

            if (type == 1) {
                TextureManager::draw(m_wall, m_sourceRectangle, m_destinationRectangle);
                Map::walls.emplace_back(m_destinationRectangle);
               // Game::addGameObject(std::make_shared<WallEntity>("../resources/img/blue.png", 25, 25, row, column, 2));

            } else if (type == 2) {
                test++;



                m_destinationRectangle.w = 5;
                m_destinationRectangle.h = 5;
                TextureManager::draw(m_pellet, m_sourceRectangle, m_destinationRectangle);
                Map::pellets.emplace_back(m_destinationRectangle);

                //Game::addGameObject(std::make_shared<Pellet>("../resources/img/pellet.png", 7, 7, row, column, 1));
                m_destinationRectangle.w = 25;
                m_destinationRectangle.h = 25;


            } else {
                TextureManager::draw(m_nonWall, m_sourceRectangle, m_destinationRectangle);
            }

        }
    }
}


#include "../include/Map.h"
