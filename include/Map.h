#ifndef EXAM_MAP_H
#define EXAM_MAP_H

#include <SDL2/SDL.h>
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
    SDL_Texture* roundedWallDown;
    SDL_Texture* roundedWallLeft;
    SDL_Texture* roundedWallRight;
    SDL_Texture* pellet;
    SDL_Texture* pelletLarge;
};


#endif
