//
// Created by mathi on 3/25/2020.
//

#ifndef EXAM_GAMEOBJECT_H
#define EXAM_GAMEOBJECT_H


#include <SDL_rect.h>
#include <SDL_render.h>
#include <string>

class GameObject {
public:
    GameObject(SDL_Texture *texturePtr, int w, int h, int x, int y, int id);

    ~GameObject();

    virtual void update() = 0;

    void render(SDL_Texture *alternativeTexture = nullptr);

    SDL_Rect m_sourceRectangle, m_positionRectangle;
    int m_id;

    virtual std::string getType() = 0;

    SDL_Texture *texture;

private:
    SDL_Renderer *renderer;
protected:
};


#endif
