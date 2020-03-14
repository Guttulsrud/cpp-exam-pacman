#ifndef CHARACTER_H
#define CHARACTER_H


#include <string>
#include <vector>
#include <SDL_render.h>
#include "Updatable.h"
#include "Component.h"

class GameObject {

public:


    GameObject(const char *textureSheet, int x, int y, int id, bool ai);

    ~GameObject();

    void update(std::vector<GameObject> &gameObjects);

    void render();



    int moveSpeed = 4;

    void setDestination(int x, int y);
    SDL_Point m_position;
    SDL_Point m_destination;
    SDL_Rect srcRect, destRect;


    int m_id;
private:
    SDL_Texture *objTexture;
    SDL_Renderer *renderer;
    bool m_ai;

    void aiFollow();
};


#endif // CHARACTER_H
