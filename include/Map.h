//
// Created by Håkon on 25.03.2020.
//

#ifndef EXAM_MAP_H
#define EXAM_MAP_H

#include <SDL.h>
#include <vector>

class Map {

public:
    Map();
    ~Map();

    void loadMap(int array[21][19]);

    void drawMap();

    int map2D[21][19];

    static std::vector<SDL_Rect> walls;

private:
    SDL_Rect m_sourceRectangle, m_destinationRectangle;
    SDL_Texture * m_wall;
    SDL_Texture * m_nonWall;
    SDL_Texture * m_pellet;
};


#endif //EXAM_MAP_H
