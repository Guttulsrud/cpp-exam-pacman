#include "../include/GameObject.h"
#include "../include/GameManager.h"


GameObject::~GameObject() {

}

void GameObject::render() {
    SDL_RenderCopy(SDLManager::m_renderer, m_texture, &m_sourceRectangle, &m_positionRectangle);
}
