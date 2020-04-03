#include "../include/GameObject.h"
#include "../include/Game.h"
#include "../include/TextureManager.h"


GameObject::GameObject(SDL_Texture *texturePtr, int w, int h, int x, int y, int id) {
    texture = texturePtr;
    m_positionRectangle.x = x;
    m_positionRectangle.y = y;
    m_positionRectangle.w = w;
    m_positionRectangle.h = h;
    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 0;
    m_sourceRectangle.h = 1600;
    m_sourceRectangle.w = 1600 ;
    m_id = id;

}

void GameObject::update() {

}

void GameObject::render(SDL_Texture *alternativeTexture) {
    if (alternativeTexture) {
        SDL_RenderCopy(Game::renderer, alternativeTexture, &m_sourceRectangle, &m_positionRectangle);
    } else {
        SDL_RenderCopy(Game::renderer, texture, &m_sourceRectangle, &m_positionRectangle);
    }
}

GameObject::~GameObject() {

}
