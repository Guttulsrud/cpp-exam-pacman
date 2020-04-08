//
// Created by Håkon on 25.03.2020.
//


#include <iostream>
#include "../include/Map.h"
#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/Pellet.h"
#include "../include/StationaryObject.h"


int levelOne[32][29] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 0, 2, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 0, 2, 1},
        {1, 0, 3, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 0, 3, 1},
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
        {1, 0, 3, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 3, 1},
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
    fill = TextureManager::loadTexture("../resources/img/walls/wall.png");
    round = TextureManager::loadTexture("../resources/img/walls/round.png");
    black = TextureManager::loadTexture("../resources/img/black.png");
    pellet = TextureManager::loadTexture("../resources/img/pellet.png");
    pelletLarge = TextureManager::loadTexture("../resources/img/pellet_large.png");

    roundedWallN = TextureManager::loadTexture("../resources/img/walls/rounded_corner_N.png");       //
    roundedWallN = TextureManager::loadTexture("../resources/img/walls/rounded_corner_N.png");       //
    roundedWallS = TextureManager::loadTexture("../resources/img/walls/rounded_corner_S.png");     //
    roundedWallW = TextureManager::loadTexture("../resources/img/walls/rounded_corner_W.png");     //
    roundedWallE = TextureManager::loadTexture("../resources/img/walls/rounded_corner_E.png");    //

    wallDoubleEdgeWE = TextureManager::loadTexture("../resources/img/walls/wall_double_edge_WE.png"); //
    wallDoubleEdgeNS = TextureManager::loadTexture("../resources/img/walls/wall_double_edge_NS.png"); //

    cornerSE = TextureManager::loadTexture("../resources/img/walls/single_corner_SE.png");            //
    cornerSW = TextureManager::loadTexture("../resources/img/walls/single_corner_SW.png");            //
    cornerNE = TextureManager::loadTexture("../resources/img/walls/single_corner_NE.png");            //
    cornerNW = TextureManager::loadTexture("../resources/img/walls/single_corner_NW.png");            //

    insideCornerNW = TextureManager::loadTexture("../resources/img/walls/inside_single_corner_NW.png");//
    insideCornerNE = TextureManager::loadTexture("../resources/img/walls/inside_single_corner_NE.png");//
    insideCornerSW = TextureManager::loadTexture("../resources/img/walls/inside_single_corner_SW.png");//
    insideCornerSE = TextureManager::loadTexture("../resources/img/walls/inside_single_corner_SE.png");//

    edgeN = TextureManager::loadTexture("../resources/img/walls/wall_single_edge_N.png");//
    edgeE = TextureManager::loadTexture("../resources/img/walls/wall_single_edge_E.png"); //
    edgeW = TextureManager::loadTexture("../resources/img/walls/wall_single_edge_W.png");//
    edgeS = TextureManager::loadTexture("../resources/img/walls/wall_single_edge_S.png");//
    loadLevelMap(levelOne);
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
        Game::addStationaryGameObject(
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
        Game::addStationaryGameObject(
                std::make_shared<StationaryObject>(HALLWAY, 0, column * tileLength + tileLength,
                                          row * tileLength + tileLength, tileTexture));
    }
}


void Map::loadLevelMap(int array[32][29]) {

    int tileType = 0;
    int idIncrementer = 0;

    for (int column = 0; column < 32; column++) {
        for (int row = 0; row < 29; row++) {
            backupArr[column][row] = array[column][row];

            tileType = array[column][row];
            idIncrementer++;
            switch (tileType) {
                case 3:
                    Game::addStationaryGameObject(std::make_shared<Pellet>(pelletLarge, row * tileLength + 25,
                            column * tileLength + 30 , idIncrementer,  15 ,15, true ));
                    break;
                case 2:
                    Game::addStationaryGameObject(
                            std::make_shared<Pellet>(pellet, row * tileLength + 30, column * tileLength + 30,
                                                     idIncrementer, 5, 5 ));
                default:
                    createWallWithTexture(array, column, row);
                    //todo: Consider different approach to large pellet positions. Will be different on other maps
            }
        }
    }
}


Map::~Map() {

}

int Map::getTileLength() const {
    return tileLength;
}
