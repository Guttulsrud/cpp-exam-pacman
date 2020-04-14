#include <iostream>
#include <fstream>
#include "../include/Map.h"
#include "../include/GameManager.h"
#include "../include/TextureManager.h"
#include "../include/Pellet.h"
#include "../include/Stationary.h"
#include "../include/Fruit.h"


Map::Map(const std::string &filePath, int mapIndex) {

    loadMapFromFile(filePath.c_str());

    round = TextureManager::loadTexture("../resources/img/walls/round.png");
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
    ///TODO: Player needs to be rendered last so that its in front
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
        GameManager::addStationaryGameObject(
                std::make_shared<Stationary>(WALL, 0, column * tileLength + tileLength,
                                             row * tileLength + tileLength, tileTexture));


    }

        ///TODO: Should check tile in corner as well

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
        GameManager::addStationaryGameObject(
                std::make_shared<Stationary>(HALLWAY, 0, column * tileLength + tileLength,
                                             row * tileLength + tileLength, tileTexture));
    }
}

void Map::loadLevelMap(int map[32][29]) {

    int tileType = 0;
    int idIncrementer = 0;

    for (int column = 0; column < 32; column++) {
        for (int row = 0; row < 29; row++) {
            currentMap[column][row] = map[column][row];

            tileType = map[column][row];
            idIncrementer++;

            switch (tileType) {
                case 4:
                    GameManager::addStationaryGameObject(std::make_shared<Fruit>(fruit, row * tileLength,
                                                                                 column * tileLength, idIncrementer, 60,
                                                                                 60, false));
                    break;
                case 3:
                    GameManager::addStationaryGameObject(std::make_shared<Pellet>(pelletLarge, row * tileLength + 25,
                                                                                  column * tileLength + 30,
                                                                                  idIncrementer, 15,
                                                                                  15, true));
                    break;
                case 2:
                    GameManager::addStationaryGameObject(
                            std::make_shared<Pellet>(pellet, row * tileLength + 30, column * tileLength + 30,
                                                     idIncrementer, 5, 5));
                default:
                    createWallWithTexture(map, column, row);
                    //todo: Consider different approach to large pellet positions. Will be different on other maps
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



