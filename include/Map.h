//
// Created by Håkon on 25.03.2020.
//

#ifndef EXAM_MAP_H
#define EXAM_MAP_H

#include <SDL.h>

class Map {

public:
    Map();
    ~Map();

    void loadMap(int array[20][20]);

    void drawMap();


private:
    SDL_Rect m_sourceRectangle, m_destinationRectangle;
    SDL_Texture * block;
    SDL_Texture * nonBlock;


    int map2D[20][20];



};


#endif //EXAM_MAP_H
