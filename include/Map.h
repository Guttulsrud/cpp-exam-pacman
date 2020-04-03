//
// Created by Håkon on 25.03.2020.
//

#ifndef EXAM_MAP_H
#define EXAM_MAP_H

#include <SDL.h>
#include <vector>
#include "Pellet.h"

class Map {

public:
    Map();
    ~Map();

    void loadLevelMap(int array[32][32]);

private:
    SDL_Texture* wall;
    SDL_Texture* roundedWallUp;
    SDL_Texture* wallDoubleEdgeWE;
    SDL_Texture* wallDoubleEdgeNS;
    SDL_Texture* roundedWallLeft;
    SDL_Texture* roundedWallDown;
    SDL_Texture* roundedWallRight;
    SDL_Texture* cornerSW;
    SDL_Texture* cornerNW;
    SDL_Texture* cornerNE;
    SDL_Texture* cornerSE;
    SDL_Texture* insideCornerNW;
    SDL_Texture* pellet;
    SDL_Texture* pelletLarge;
};


#endif //EXAM_MAP_H
