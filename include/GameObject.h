#ifndef EXAM_GAMEOBJECT_H
#define EXAM_GAMEOBJECT_H

#include <string>
#include <SDL2/SDL.h>
#include "TextureManager.h"

enum class Direction {
    UP, DOWN, LEFT, RIGHT, NONE
};

class GameObject {
public:
    GameObject(int w, int h, int x, int y) {
        m_positionRectangle.x = x;
        m_positionRectangle.y = y;
        m_positionRectangle.w = w;
        m_positionRectangle.h = h;
        m_sourceRectangle.x = 0;
        m_sourceRectangle.y = 0;
        m_sourceRectangle.h = 1600;
        m_sourceRectangle.w = 1600;
    }

    void render();
    SDL_Rect m_sourceRectangle, m_positionRectangle;
    SDL_Texture *m_texture;

};


#endif
