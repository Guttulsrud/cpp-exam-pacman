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
    SDL_Texture* pellet;
    SDL_Texture* pelletLarge;
};


#endif //EXAM_MAP_H
