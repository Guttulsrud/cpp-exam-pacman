#include "../include/GameObject.h"
#include "../include/Game.h"


GameObject::~GameObject() {

}

void GameObject::render() {
    SDL_RenderCopy(Game::renderer, m_texture, &m_sourceRectangle, &m_positionRectangle);
}
