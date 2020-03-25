//
// Created by mathi on 3/25/2020.
//

#include "../include/GameObject.h"
#include "../include/Game.h"
#include "../include/TextureManager.h"


GameObject::GameObject(const char *textureSheet, int w, int h, int x, int y, int id) {

    texture = TextureManager::loadTexture(textureSheet);
    m_positionRectangle.x = x;
    m_positionRectangle.y = y;
    m_positionRectangle.w = w;
    m_positionRectangle.h = h;
    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 0;
    m_sourceRectangle.h = 1080;
    m_sourceRectangle.w = 1920;
    m_id = id;

}

void GameObject::update() {

}

void GameObject::render() {
    SDL_RenderCopy(Game::renderer, texture, &m_sourceRectangle, &m_positionRectangle);
}


GameObject::~GameObject() {

}
