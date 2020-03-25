//
// Created by mathi on 3/25/2020.
//

#ifndef EXAM_GAMEOBJECT_H
#define EXAM_GAMEOBJECT_H


#include <SDL_rect.h>
#include <SDL_render.h>

class GameObject {
public:
    GameObject(const char *textureSheet, int w, int h, int x, int y, int id);
    ~GameObject();
    virtual void update() = 0;
    void render();
    SDL_Rect m_sourceRectangle, m_positionRectangle;
    int m_id;
private:
    SDL_Texture * texture;
    SDL_Renderer * renderer;
};


#endif //EXAM_GAMEOBJECT_H
