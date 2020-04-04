#ifndef EXAM_GAMEOBJECT_H
#define EXAM_GAMEOBJECT_H

#include <string>
#include <SDL2/SDL.h>
#include "TextureManager.h"

enum TYPE{
    PLAYER,
    GHOST,
    WALL,
    PELLET,
    HALLWAY,
    VOIDWARP
};
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};



class GameObject {
public:
    GameObject(SDL_Texture *texturePtr, int w, int h, int x, int y, int id);

    ~GameObject();

    virtual void update() = 0;

    void render(SDL_Texture *alternativeTexture = nullptr);

    SDL_Rect m_sourceRectangle, m_positionRectangle;
    int m_id;

    virtual TYPE getType() = 0;

    SDL_Texture *texture;

private:
    SDL_Renderer *renderer;
};


#endif
