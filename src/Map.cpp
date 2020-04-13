#include <iostream>
#include <fstream>
#include "../include/Map.h"
#include "../include/GameManager.h"
#include "../include/TextureManager.h"
#include "../include/Pellet.h"
#include "../include/StationaryObject.h"
#include "../include/Fruit.h"


Map::Map(const char *filePath) {

    loadMapFromFile(filePath);


    round = TextureManager::loadTexture("../resources/img/walls/round.png");
    black = TextureManager::loadTexture("../resources/img/black.png");

    if(GameManager::getInstance().activeMap == 1){

        fill = TextureManager::loadTexture("../resources/img/walls/wall.png");
        pellet = TextureManager::loadTexture("../resources/img/pickups/pellet.png");
        pelletLarge = TextureManager::loadTexture("../resources/img/pickups/power_pellet.png");

        roundedWallN = TextureManager::loadTexture("../resources/img/walls/rounded_corner_N.png");
        roundedWallS = TextureManager::loadTexture("../resources/img/walls/rounded_corner_S.png");
        roundedWallW = TextureManager::loadTexture("../resources/img/walls/rounded_corner_W.png");
        roundedWallE = TextureManager::loadTexture("../resources/img/walls/rounded_corner_E.png");

        wallDoubleEdgeWE = TextureManager::loadTexture("../resources/img/walls/wall_double_edge_WE.png");
        wallDoubleEdgeNS = TextureManager::loadTexture("../resources/img/walls/wall_double_edge_NS.png");

        cornerSE = TextureManager::loadTexture("../resources/img/walls/single_corner_SE.png");
        cornerSW = TextureManager::loadTexture("../resources/img/walls/single_corner_SW.png");
        cornerNE = TextureManager::loadTexture("../resources/img/walls/single_corner_NE.png");
        cornerNW = TextureManager::loadTexture("../resources/img/walls/single_corner_NW.png");

        insideCornerNW = TextureManager::loadTexture("../resources/img/walls/inside_single_corner_NW.png");
        insideCornerNE = TextureManager::loadTexture("../resources/img/walls/inside_single_corner_NE.png");
        insideCornerSW = TextureManager::loadTexture("../resources/img/walls/inside_single_corner_SW.png");
        insideCornerSE = TextureManager::loadTexture("../resources/img/walls/inside_single_corner_SE.png");

        edgeN = TextureManager::loadTexture("../resources/img/walls/wall_single_edge_N.png");
        edgeE = TextureManager::loadTexture("../resources/img/walls/wall_single_edge_E.png");
        edgeW = TextureManager::loadTexture("../resources/img/walls/wall_single_edge_W.png");
        edgeS = TextureManager::loadTexture("../resources/img/walls/wall_single_edge_S.png");

        fruit = TextureManager::loadTexture("../resources/img/pickups/cherry.png");

    } else if (GameManager::getInstance().activeMap == 2){

        fill = TextureManager::loadTexture("../resources/img/walls_red/wall_red.png");
        pellet = TextureManager::loadTexture("../resources/img/pickups/pellet_orange.png");
        pelletLarge = TextureManager::loadTexture("../resources/img/pickups/power_pellet.png");

        roundedWallN = TextureManager::loadTexture("../resources/img/walls_red/rounded_corner_red_N.png");
        roundedWallS = TextureManager::loadTexture("../resources/img/walls_red/rounded_corner_red_S.png");
        roundedWallW = TextureManager::loadTexture("../resources/img/walls_red/rounded_corner_red_W.png");
        roundedWallE = TextureManager::loadTexture("../resources/img/walls_red/rounded_corner_red_E.png");

        wallDoubleEdgeWE = TextureManager::loadTexture("../resources/img/walls_red/wall_double_edge_red_WE.png");
        wallDoubleEdgeNS = TextureManager::loadTexture("../resources/img/walls_red/wall_double_edge_red_NS.png");

        cornerSE = TextureManager::loadTexture("../resources/img/walls_red/single_corner_red_SE.png");
        cornerSW = TextureManager::loadTexture("../resources/img/walls_red/single_corner_red_SW.png");
        cornerNE = TextureManager::loadTexture("../resources/img/walls_red/single_corner_red_NE.png");
        cornerNW = TextureManager::loadTexture("../resources/img/walls_red/single_corner_red_NW.png");

        insideCornerNW = TextureManager::loadTexture("../resources/img/walls_red/inside_single_corner_red_NW.png");
        insideCornerNE = TextureManager::loadTexture("../resources/img/walls_red/inside_single_corner_red_NE.png");
        insideCornerSW = TextureManager::loadTexture("../resources/img/walls_red/inside_single_corner_red_SW.png");
        insideCornerSE = TextureManager::loadTexture("../resources/img/walls_red/inside_single_corner_red_SE.png");

        edgeN = TextureManager::loadTexture("../resources/img/walls_red/wall_single_edge_red_N.png");
        edgeE = TextureManager::loadTexture("../resources/img/walls_red/wall_single_edge_red_E.png");
        edgeW = TextureManager::loadTexture("../resources/img/walls_red/wall_single_edge_red_W.png");
        edgeS = TextureManager::loadTexture("../resources/img/walls_red/wall_single_edge_red_S.png");

        fruit = TextureManager::loadTexture("../resources/img/pickups/melon.png");


    } else if (GameManager::getInstance().activeMap == 3){

        fill = TextureManager::loadTexture("../resources/img/walls_green/wall_green.png");
        pellet = TextureManager::loadTexture("../resources/img/pickups/pellet_cyan.png");
        pelletLarge = TextureManager::loadTexture("../resources/img/pickups/power_pellet_yellow.png");

        roundedWallN = TextureManager::loadTexture("../resources/img/walls_green/rounded_corner_green_N.png");
        roundedWallS = TextureManager::loadTexture("../resources/img/walls_green/rounded_corner_green_S.png");
        roundedWallW = TextureManager::loadTexture("../resources/img/walls_green/rounded_corner_green_W.png");
        roundedWallE = TextureManager::loadTexture("../resources/img/walls_green/rounded_corner_green_E.png");

        wallDoubleEdgeWE = TextureManager::loadTexture("../resources/img/walls_green/wall_double_edge_green_WE.png");
        wallDoubleEdgeNS = TextureManager::loadTexture("../resources/img/walls_green/wall_double_edge_green_NS.png");

        cornerSE = TextureManager::loadTexture("../resources/img/walls_green/single_corner_green_SE.png");
        cornerSW = TextureManager::loadTexture("../resources/img/walls_green/single_corner_green_SW.png");
        cornerNE = TextureManager::loadTexture("../resources/img/walls_green/single_corner_green_NE.png");
        cornerNW = TextureManager::loadTexture("../resources/img/walls_green/single_corner_green_NW.png");

        insideCornerNW = TextureManager::loadTexture("../resources/img/walls_green/inside_single_corner_green_NW.png");
        insideCornerNE = TextureManager::loadTexture("../resources/img/walls_green/inside_single_corner_green_NE.png");
        insideCornerSW = TextureManager::loadTexture("../resources/img/walls_green/inside_single_corner_green_SW.png");
        insideCornerSE = TextureManager::loadTexture("../resources/img/walls_green/inside_single_corner_green_SE.png");

        edgeN = TextureManager::loadTexture("../resources/img/walls_green/wall_single_edge_green_N.png");
        edgeE = TextureManager::loadTexture("../resources/img/walls_green/wall_single_edge_green_E.png");
        edgeW = TextureManager::loadTexture("../resources/img/walls_green/wall_single_edge_green_W.png");
        edgeS = TextureManager::loadTexture("../resources/img/walls_green/wall_single_edge_green_S.png");

        fruit = TextureManager::loadTexture("../resources/img/pickups/strawberry.png");

    }

    loadLevelMap(currentMap);
}

void Map::createWallWithTexture(int map[32][29], int row, int column) {
    ///TODO: Player needs to be rendered last so that its in front
    int wall = 1;

    int westTile = map[row][column - 1] == wall ? wall : 0;
    int eastTile = map[row][column + 1] == wall ? wall : 0;
    int northTile = map[row - 1][column] == wall ? wall : 0;
    int southTile = map[row + 1][column] == wall ? wall : 0;

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
            if (southTile == wall) tileTexture = roundedWallN;
            if (northTile == wall) tileTexture = roundedWallS;
            if (eastTile == wall) tileTexture = roundedWallW;
            if (westTile == wall) tileTexture = roundedWallE;

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
                std::make_shared<StationaryObject>(WALL, 0, column * tileLength + tileLength,
                                                   row * tileLength + tileLength, tileTexture));


    }

        ///TODO: Should check tile in corner as well

    else if (tileType != wall && wallNeighbours == 2) {
        if (southTile == wall) {
            if (westTile == wall) {
                tileTexture = insideCornerSW;
            } else if (northTile == wall) {
                tileTexture = black;
            } else {
                tileTexture = insideCornerSE;
            }
        } else {
            if (westTile == wall && eastTile == wall) {
                tileTexture = black;
            } else if (westTile == wall) {
                tileTexture = insideCornerNW;
            } else {
                tileTexture = insideCornerNE;
            }
        }
        GameManager::addStationaryGameObject(
                std::make_shared<StationaryObject>(HALLWAY, 0, column * tileLength + tileLength,
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
                                                                           column * tileLength + 30, idIncrementer, 15,
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



