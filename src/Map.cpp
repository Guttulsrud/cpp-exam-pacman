#include <iostream>
#include <fstream>
#include "../include/Map.h"
#include "../include/GameManager.h"

Map::Map(const std::string &filePath, int mapIndex) {

    loadMapFromFile(filePath.c_str());

    std::string folderPath;

    switch (mapIndex) {
        case 0:
            folderPath = "../resources/img/walls/blue/";
            m_pellet = TextureManager::loadTexture("../resources/img/pickups/pellet.png");
            m_pelletLarge = TextureManager::loadTexture("../resources/img/pickups/power_pellet.png");
            break;
        case 1:

            folderPath = "../resources/img/walls/red/";
            m_pellet = TextureManager::loadTexture("../resources/img/pickups/pellet_orange.png");
            m_pelletLarge = TextureManager::loadTexture("../resources/img/pickups/power_pellet.png");
            break;
        case 2:
            folderPath = "../resources/img/walls/green/";
            m_pellet = TextureManager::loadTexture("../resources/img/pickups/pellet_cyan.png");
            m_pelletLarge = TextureManager::loadTexture("../resources/img/pickups/power_pellet_yellow.png");
            break;
        default:
            folderPath = "../resources/img/walls/blue/";
            break;
    }


    m_round = TextureManager::loadTexture(folderPath + "round.png");
    m_fill = TextureManager::loadTexture(folderPath + "default.png");

    m_endN = TextureManager::loadTexture(folderPath + "end_N.png");
    m_endS = TextureManager::loadTexture(folderPath + "end_S.png");
    m_endW = TextureManager::loadTexture(folderPath + "end_W.png");
    m_endE = TextureManager::loadTexture(folderPath + "end_E.png");

    m_wallDoubleEdgeWE = TextureManager::loadTexture(folderPath + "double_edge_WE.png");
    m_wallDoubleEdgeNS = TextureManager::loadTexture(folderPath + "double_edge_NS.png");

    m_cornerSE = TextureManager::loadTexture(folderPath + "outer_corner_SE.png");
    m_cornerSW = TextureManager::loadTexture(folderPath + "outer_corner_SW.png");
    m_cornerNE = TextureManager::loadTexture(folderPath + "outer_corner_NE.png");
    m_cornerNW = TextureManager::loadTexture(folderPath + "outer_corner_NW.png");

    m_insideCornerNW = TextureManager::loadTexture(folderPath + "inner_corner_NW.png");
    m_insideCornerNE = TextureManager::loadTexture(folderPath + "inner_corner_NE.png");
    m_insideCornerSW = TextureManager::loadTexture(folderPath + "inner_corner_SW.png");
    m_insideCornerSE = TextureManager::loadTexture(folderPath + "inner_corner_SE.png");

    m_edgeN = TextureManager::loadTexture(folderPath + "edge_N.png");
    m_edgeE = TextureManager::loadTexture(folderPath + "edge_E.png");
    m_edgeW = TextureManager::loadTexture(folderPath + "edge_W.png");
    m_edgeS = TextureManager::loadTexture(folderPath + "edge_S.png");

    m_fruitMapOne = TextureManager::loadTexture("../resources/img/pickups/cherry.png");
    m_fruitMapTwo = TextureManager::loadTexture("../resources/img/pickups/melon.png");
    m_fruitMapThree = TextureManager::loadTexture("../resources/img/pickups/strawberry.png");


    loadLevelMap(m_currentMap);
}

void Map::createWallWithTexture(int map[32][29], int row, int column) {
    int wall = 1;

    int westTile = map[row][column - 1] == wall ? wall : 0;
    int eastTile = map[row][column + 1] == wall ? wall : 0;
    int northTile = map[row - 1][column] == wall ? wall : 0;
    int southTile = map[row + 1][column] == wall ? wall : 0;


    int nwTile = map[row - 1][column - 1] == wall ? wall : 0;
    int neTile = map[row - 1][column + 1] == wall ? wall : 0;
    int swTile = map[row + 1][column - 1] == wall ? wall : 0;
    int seTile = map[row + 1][column + 1] == wall ? wall : 0;

    //sets padding to 0
    if (column - 1 < 0) {
        westTile = 0;
    }
    if (column + 1 == 29) {
        eastTile = 0;
    }
    if (row - 1 < 0) {
        northTile = 0;
    }
    if (row + 1 == 32) {
        southTile = 0;
    }

    int tileType = map[row][column];

    int wallNeighbours = 0;
    if (southTile == wall)wallNeighbours++;
    if (northTile == wall)wallNeighbours++;
    if (westTile == wall)wallNeighbours++;
    if (eastTile == wall)wallNeighbours++;

    SDL_Texture *tileTexture;


    if (tileType == wall) {
        if (wallNeighbours == 0) {
            tileTexture = m_round;
        } else if (wallNeighbours == 1) {
            if (southTile == wall) tileTexture = m_endN;
            if (northTile == wall) tileTexture = m_endS;
            if (eastTile == wall) tileTexture = m_endW;
            if (westTile == wall) tileTexture = m_endE;

        } else if (wallNeighbours == 2) {
            if (southTile == wall) {
                if (northTile == wall) {
                    tileTexture = m_wallDoubleEdgeWE;
                } else if (westTile == wall) {
                    tileTexture = m_cornerNE;
                } else {
                    tileTexture = m_cornerNW;
                }
            } else if (westTile == wall) {
                if (eastTile == wall) {
                    tileTexture = m_wallDoubleEdgeNS;
                } else {
                    tileTexture = m_cornerSE;
                }
            } else {
                tileTexture = m_cornerSW;
            }
        } else if (wallNeighbours == 3) {
            if (northTile != wall) tileTexture = m_edgeN;
            if (southTile != wall) tileTexture = m_edgeS;
            if (westTile != wall) tileTexture = m_edgeW;
            if (eastTile != wall) tileTexture = m_edgeE;
        } else {
            tileTexture = m_fill;
        }
        GameManager::addStationary(
                std::make_shared<Stationary>(WALL, column * m_tileLength + m_tileLength,
                                             row * m_tileLength + m_tileLength, tileTexture));


    }
    else if (tileType != wall && wallNeighbours == 2) {
        if ((northTile == wall && southTile == wall) || (eastTile == wall && westTile == wall)) {
            return;
        } else if (southTile == wall) {
            if (westTile == wall && swTile == wall) {
                tileTexture = m_insideCornerSW;
            } else if (seTile == wall) {
                tileTexture = m_insideCornerSE;
            }
        } else {
            if (westTile == wall && nwTile == wall) {
                tileTexture = m_insideCornerNW;
            } else {
                tileTexture = m_insideCornerNE;
            }
        }
        GameManager::addStationary(
                std::make_shared<Stationary>(HALLWAY, column * m_tileLength + m_tileLength,
                                             row * m_tileLength + m_tileLength, tileTexture));
    }
}

void Map::loadLevelMap(int map[32][29]) {

    int tileType = 0;

    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 29; column++) {
            m_currentMap[row][column] = map[row][column];

            tileType = map[row][column];

            switch (tileType) {
                case 6:
                    GameManager::addPellet(
                            std::make_shared<Pellet>(m_fruitMapThree, column * m_tileLength + 30, row * m_tileLength + 30, 50, 50, false, true));
                    break;
                case 5:
                    GameManager::addPellet(
                            std::make_shared<Pellet>(m_fruitMapTwo, column * m_tileLength + 30, row * m_tileLength + 30, 50, 50, false, true));
                    break;
                case 4:
                    GameManager::addPellet(
                            std::make_shared<Pellet>(m_fruitMapOne, column * m_tileLength + 30, row * m_tileLength + 30, 50, 50, false, true));
                    break;
                case 3:
                    GameManager::addPellet(std::make_shared<Pellet>(m_pelletLarge, column * m_tileLength + 30 - 8,
                                                                    row * m_tileLength + 30 - 8, 16,
                                                                    16, true));
                    break;
                case 2:
                    GameManager::addPellet(
                            std::make_shared<Pellet>(m_pellet, column * m_tileLength + 30 - 5, row * m_tileLength + 30 - 5, 10, 10));

                default:
                    createWallWithTexture(map, row, column);
            }
        }
    }
}



void Map::loadMapFromFile(const char *filePath) {

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Can't open map!" << std::endl;
    }

    for (int column = 0; column != 32; column++) {
        for (int row = 0; row != 29; row++) {
            file >> m_currentMap[column][row];
        }
    }
}




