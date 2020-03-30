//
// Created by Håkon on 25.03.2020.
//


#include "../include/Map.h"
#include "../include/Game.h"
#include "../include/TextureManager.h"


int levelOne[21][19] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1},
        {1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


Map::Map() {
    m_wall = Game::loadTexture("../resources/img/blue.png");
    m_nonWall = Game::loadTexture("../resources/img/black.png");
    m_pellet = Game::loadTexture("../resources/img/pellet.png");


    loadMap(levelOne);

    m_sourceRectangle.x = m_sourceRectangle.y = 0;
    m_sourceRectangle.w = m_destinationRectangle.w = 40;
    m_sourceRectangle.h = m_destinationRectangle.h = 40;

    m_destinationRectangle.x = m_destinationRectangle.y = 0;


}

void Map::loadMap(int array[21][19]) {
    for (int row = 0; row < 21; row++) {
        for (int column = 0; column < 19; column++) {
            map2D[row][column] = array[row][column];
        }
    }
}

std::vector<SDL_Rect> Map::walls;


void Map::drawMap() {
    int type = 0;


    for (int row = 0; row < 21; row++) {
        for (int column = 0; column < 19; column++) {
            type = map2D[row][column];

            m_destinationRectangle.x = column * 40;
            m_destinationRectangle.y = row * 40;


            if (type == 1) {
                TextureManager::draw(m_wall, m_sourceRectangle, m_destinationRectangle);

                Map::walls.push_back(m_destinationRectangle);

            } else if (type == 2) {
                TextureManager::draw(m_pellet, m_sourceRectangle, m_destinationRectangle);

            } else {
                TextureManager::draw(m_nonWall, m_sourceRectangle, m_destinationRectangle);
            }

        }
    }
}


#include "../include/Map.h"
