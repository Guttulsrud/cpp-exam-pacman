//
// Created by Håkon on 25.03.2020.
//


#include <iostream>
#include "../include/Map.h"
#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/WallEntity.h"


int levelOne[32][32] = {
        {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
        {1 , 15, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 7 , 15, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
        {1 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 },
        {1 , 0 , 0 , 12, 1 , 13, 0 , 2 , 12, 1 , 1 , 13, 0 , 2 , 7 , 0 , 2 , 12, 1 , 1 , 13, 0 , 2 , 12, 1 , 13, 0 , 2 , 1 },
        {1 , 0 , 5 , 11, 1 , 14, 0 , 2 , 11, 1 , 1 , 14, 0 , 2 , 10, 0 , 2 , 11, 1 , 1 , 14, 0 , 2 , 11, 1 , 14, 0 , 3 , 1 },
        {1 , 0 , 2 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 2 , 1 },
        {1 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 },
        {1 , 0 , 2 , 8 , 16, 9 , 0 , 2 , 6 , 0 , 2 , 8 , 16, 16, 1 , 16, 16, 9 , 0 , 2 , 6 , 0 , 2 , 8 , 16, 9 , 0 , 2 , 1 },
        {1 , 0 , 2 , 0 , 0 , 0 , 0 , 2 , 7 , 0 , 2 , 0 , 0 , 0 , 7 , 15, 0 , 0 , 0 , 2 , 7 , 0 , 2 , 0 , 0 , 0 , 0 , 2 , 1 },
        {1 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 1 },
        {1 , 1 , 1 , 1 , 1 , 13, 0 , 2 , 1 , 16, 16, 9 , 0 , 2 , 10, 0 , 2 , 8 , 16, 16, 1 , 0 , 2 , 12, 1 , 1 , 1 , 1 , 1 },
        {0 , 0 , 0 , 0 , 0 , 1 , 0 , 2 , 7 , 15, 0 , 0 , 0 , 2 , 0 , 0 , 2 , 0 , 0 , 0 , 7 , 0 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 0 , 1 , 0 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
        {1 , 1 , 1 , 1 , 1 , 14, 0 , 2 , 10, 0 , 2 , 12, 16, 16, 16, 16, 16, 13, 0 , 2 , 10, 0 , 2 , 11, 1 , 1 , 1 , 1 , 1 },
        {0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 2 , 7 , 15, 0 , 0 , 0 , 0 , 7 , 0 , 2 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 },
        {2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 7 , 0 , 0 , 0 , 0 , 0 , 7 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 },
        {1 , 1 , 1 , 1 , 1 , 13, 0 , 2 , 6 , 0 , 2 , 11, 16, 16, 16, 16, 16, 14, 0 , 2 , 6 , 0 , 2 , 12, 1 , 1 , 1 , 1 , 1 },
        {0 , 0 , 0 , 0 , 0 , 1 , 0 , 2 , 7 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 7 , 0 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
        {0 , 0 , 0 , 0 , 0 , 1 , 0 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 1 , 0 , 0 , 0 , 0 , 0 },
        {1 , 1 , 1 , 1 , 1 , 14, 0 , 2 , 10, 0 , 2 , 8 , 16, 16, 1 , 16, 16, 9 , 0 , 2 , 10, 0 , 2 , 11, 1 , 1 , 1 , 1 , 1 },
        {1 , 15, 0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 2 , 0 , 0 , 0 , 7 , 15, 0 , 0 , 0 , 2 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 1 },
        {1 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 },
        {1 , 0 , 2 , 8 , 16, 13, 0 , 2 , 8 , 16, 16, 9 , 0 , 2 , 10, 0 , 2 , 8 , 16, 16, 9 , 0 , 2 , 12, 16, 9 , 0 , 2 , 1 },
        {1 , 0 , 5 , 0 , 0 , 7 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 2 , 7 , 15, 0 , 0 , 4 , 1 },
        {1 , 0 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 1 },
        {1 , 16, 9 , 0 , 2 , 10, 0 , 2 , 6 , 0 , 2 , 8 , 16, 16, 1 , 16, 16, 9 , 0 , 2 , 6 , 0 , 2 , 10, 0 , 2 , 8 , 16, 1 },
        {1 , 15, 0 , 0 , 2 , 0 , 0 , 2 , 7 , 0 , 2 , 0 , 0 , 0 , 7 , 15, 0 , 0 , 0 , 2 , 7 , 0 , 2 , 0 , 0 , 2 , 0 , 0 , 1 },
        {1 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 7 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 1 },
        {1 , 0 , 2 , 8 , 16, 16, 16, 16, 1 , 16, 16, 9 , 0 , 2 , 10, 0 , 2 , 8 , 16, 16, 1 , 16, 16, 16, 16, 9 , 0 , 2 , 1 },
        {1 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 1 },
        {1 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 1 },
        {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 }
};


Map::Map() {
    wall = TextureManager::loadTexture("../resources/img/walls/wall.png");
    pellet = TextureManager::loadTexture("../resources/img/pellet.png");
    pelletLarge = TextureManager::loadTexture("../resources/img/pellet_large.png");
    roundedWallUp = TextureManager::loadTexture("../resources/img/walls/rounded_corner_N.png");       //6
    roundedWallDown = TextureManager::loadTexture("../resources/img/walls/rounded_corner_S.png");     //10
    wallDoubleEdgeWE = TextureManager::loadTexture("../resources/img/walls/wall_double_edge_WE.png"); //7
    wallDoubleEdgeNS = TextureManager::loadTexture("../resources/img/walls/wall_double_edge_NS.png"); //16
    roundedWallLeft = TextureManager::loadTexture("../resources/img/walls/rounded_corner_W.png");     //8
    roundedWallRight = TextureManager::loadTexture("../resources/img/walls/rounded_corner_E.png");    //9
    cornerSE = TextureManager::loadTexture("../resources/img/walls/single_corner_SE.png");            //14
    cornerSW = TextureManager::loadTexture("../resources/img/walls/single_corner_SW.png");            //11
    cornerNE = TextureManager::loadTexture("../resources/img/walls/single_corner_NE.png");            //13
    cornerNW = TextureManager::loadTexture("../resources/img/walls/single_corner_NW.png");            //12
    insideCornerNW = TextureManager::loadTexture("../resources/img/walls/inside_single_corner_NW.png");//15


    loadLevelMap(levelOne);
}


void Map::loadLevelMap(int array[32][32]) {
    int tileType = 0;
    int idIncrementer = 0;
    int tileLength = 30;

    for (int column = 0; column < 32; column++) {
        for (int row = 0; row < 32; row++) {

            tileType = array[column][row];
            idIncrementer++;
            switch (tileType) {
                case 1:
                    Game::addGameObject(std::make_shared<WallEntity>(wall, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 2:
                    Game::addGameObject(std::make_shared<Pellet>(pellet, 5, 5, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 3:
                    Game::addGameObject(std::make_shared<Pellet>(pelletLarge, 15, 15, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 4:
                    Game::addGameObject(std::make_shared<Pellet>(pelletLarge, 15, 15, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 5:
                    Game::addGameObject(std::make_shared<Pellet>(pelletLarge, 15, 15, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 6:
                    Game::addGameObject(std::make_shared<WallEntity>(roundedWallUp, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 7:
                    Game::addGameObject(std::make_shared<WallEntity>(wallDoubleEdgeWE, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 8:
                    Game::addGameObject(std::make_shared<WallEntity>(roundedWallLeft, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 9:
                    Game::addGameObject(std::make_shared<WallEntity>(roundedWallRight, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 10:
                    Game::addGameObject(std::make_shared<WallEntity>(roundedWallDown, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 11:
                    Game::addGameObject(std::make_shared<WallEntity>(cornerSW, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 12:
                    Game::addGameObject(std::make_shared<WallEntity>(cornerNW, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 13:
                    Game::addGameObject(std::make_shared<WallEntity>(cornerNE, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 14:
                    Game::addGameObject(std::make_shared<WallEntity>(cornerSE, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 15:
                    Game::addGameObject(std::make_shared<WallEntity>(insideCornerNW, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                case 16:
                    Game::addGameObject(std::make_shared<WallEntity>(wallDoubleEdgeNS, tileLength, tileLength, row * tileLength+30, column * tileLength+30, idIncrementer));
                    break;
                default:;
                //todo: Consider different approach to large pellet positions. Will be different on other maps
            }
        }
    }
}


Map::~Map() {

}
