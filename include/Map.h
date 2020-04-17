#ifndef EXAM_MAP_H
#define EXAM_MAP_H

#include <SDL2/SDL.h>
#include <vector>
#include <map>

class Map {


public:
    Map(const std::string& filePath, int mapIndex);

private:
    void createWallWithTexture(int map[32][29], int row, int column);
    void loadLevelMap(int map[32][29]);
    void loadMapFromFile(const char *filePath);

    int m_tileLength = 30;
    int m_currentMap[32][29];

    SDL_Texture *m_fill;
    SDL_Texture *m_round;
    SDL_Texture *m_wall;
    SDL_Texture *m_endN;
    SDL_Texture *m_endW;
    SDL_Texture *m_endS;
    SDL_Texture *m_endE;
    SDL_Texture *m_wallDoubleEdgeWE;
    SDL_Texture *m_wallDoubleEdgeNS;
    SDL_Texture *m_cornerSW;
    SDL_Texture *m_cornerNW;
    SDL_Texture *m_cornerNE;
    SDL_Texture *m_cornerSE;
    SDL_Texture *m_insideCornerNW;
    SDL_Texture *m_insideCornerNE;
    SDL_Texture *m_insideCornerSW;
    SDL_Texture *m_insideCornerSE;
    SDL_Texture *m_edgeS;
    SDL_Texture *m_edgeN;
    SDL_Texture *m_edgeE;
    SDL_Texture *m_edgeW;
    SDL_Texture *m_pellet;
    SDL_Texture *m_pelletLarge;
    SDL_Texture *m_fruitMapOne;
    SDL_Texture *m_fruitMapTwo;
    SDL_Texture *m_fruitMapThree;
};


#endif
