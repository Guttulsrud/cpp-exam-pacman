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
            pellet = TextureManager::loadTexture("../resources/img/pickups/pellet.png");
            pelletLarge = TextureManager::loadTexture("../resources/img/pickups/power_pellet.png");
            break;
        case 1:

            folderPath = "../resources/img/walls/red/";
            pellet = TextureManager::loadTexture("../resources/img/pickups/pellet_orange.png");
            pelletLarge = TextureManager::loadTexture("../resources/img/pickups/power_pellet.png");
            break;
        case 2:
            folderPath = "../resources/img/walls/green/";
            pellet = TextureManager::loadTexture("../resources/img/pickups/pellet_cyan.png");
            pelletLarge = TextureManager::loadTexture("../resources/img/pickups/power_pellet_yellow.png");
            break;
        default:
            folderPath = "../resources/img/walls/blue/";
            break;
    }


    round = TextureManager::loadTexture(folderPath + "round.png");
    fill = TextureManager::loadTexture(folderPath + "default.png");

    endN = TextureManager::loadTexture(folderPath + "end_N.png");
    endS = TextureManager::loadTexture(folderPath + "end_S.png");
    endW = TextureManager::loadTexture(folderPath + "end_W.png");
    endE = TextureManager::loadTexture(folderPath + "end_E.png");

    wallDoubleEdgeWE = TextureManager::loadTexture(folderPath + "double_edge_WE.png");
    wallDoubleEdgeNS = TextureManager::loadTexture(folderPath + "double_edge_NS.png");

    cornerSE = TextureManager::loadTexture(folderPath + "outer_corner_SE.png");
    cornerSW = TextureManager::loadTexture(folderPath + "outer_corner_SW.png");
    cornerNE = TextureManager::loadTexture(folderPath + "outer_corner_NE.png");
    cornerNW = TextureManager::loadTexture(folderPath + "outer_corner_NW.png");

    insideCornerNW = TextureManager::loadTexture(folderPath + "inner_corner_NW.png");
    insideCornerNE = TextureManager::loadTexture(folderPath + "inner_corner_NE.png");
    insideCornerSW = TextureManager::loadTexture(folderPath + "inner_corner_SW.png");
    insideCornerSE = TextureManager::loadTexture(folderPath + "inner_corner_SE.png");

    edgeN = TextureManager::loadTexture(folderPath + "edge_N.png");
    edgeE = TextureManager::loadTexture(folderPath + "edge_E.png");
    edgeW = TextureManager::loadTexture(folderPath + "edge_W.png");
    edgeS = TextureManager::loadTexture(folderPath + "edge_S.png");

    fruit = TextureManager::loadTexture("../resources/img/pickups/strawberry.png");


    loadLevelMap(currentMap);
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
            tileTexture = round;
        } else if (wallNeighbours == 1) {
            if (southTile == wall) tileTexture = endN;
            if (northTile == wall) tileTexture = endS;
            if (eastTile == wall) tileTexture = endW;
            if (westTile == wall) tileTexture = endE;

        } else if (wallNeighbours == 2) {
            if (southTile == wall) {
                if (northTile == wall) {
                    tileTexture = wallDoubleEdgeWE;
                } else if (westTile == wall) {
                    tileTexture = cornerNE;
                } else {
                    tileTexture = cornerNW;
                }
            } else if (westTile == wall) {
                if (eastTile == wall) {
                    tileTexture = wallDoubleEdgeNS;
                } else {
                    tileTexture = cornerSE;
                }
            } else {
                tileTexture = cornerSW;
            }
        } else if (wallNeighbours == 3) {
            if (northTile != wall) tileTexture = edgeN;
            if (southTile != wall) tileTexture = edgeS;
            if (westTile != wall) tileTexture = edgeW;
            if (eastTile != wall) tileTexture = edgeE;
        } else {
            tileTexture = fill;
        }
        GameManager::addStationary(
                std::make_shared<Stationary>(WALL, column * tileLength + tileLength,
                                             row * tileLength + tileLength, tileTexture));


    }
    else if (tileType != wall && wallNeighbours == 2) {
        if ((northTile == wall && southTile == wall) || (eastTile == wall && westTile == wall)) {
            tileTexture = black;
        } else if (southTile == wall) {
            if (westTile == wall && swTile == wall) {
                tileTexture = insideCornerSW;
            } else if (seTile == wall) {
                tileTexture = insideCornerSE;
            }
        } else {
            if (westTile == wall && nwTile == wall) {
                tileTexture = insideCornerNW;
            } else {
                tileTexture = insideCornerNE;
            }
        }
        GameManager::addStationary(
                std::make_shared<Stationary>(HALLWAY, column * tileLength + tileLength,
                                             row * tileLength + tileLength, tileTexture));
    }
}

void Map::loadLevelMap(int map[32][29]) {

    int tileType = 0;

    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 29; column++) {
            currentMap[row][column] = map[row][column];

            tileType = map[row][column];

            switch (tileType) {
                case 4:
                    GameManager::addPellet(
                            std::make_shared<Pellet>(fruit, column * tileLength + 30, row * tileLength + 30, 50, 50, false, true));
                    break;
                case 3:
                    GameManager::addPellet(std::make_shared<Pellet>(pelletLarge, column * tileLength + 30 -8,
                                                                    row * tileLength + 30 -8, 16,
                                                                    16, true));
                    break;
                case 2:
                    GameManager::addPellet(
                            std::make_shared<Pellet>(pellet, column * tileLength + 30 - 5, row * tileLength + 30 - 5, 10, 10));

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
            file >> currentMap[column][row];
        }
    }
}

Map::~Map() {

}



