#include "../include/GameObject.h"
#include "../include/GameManager.h"

void GameObject::render() {
    SDLManager::getInstance().render(m_texture, &m_sourceRectangle, &m_positionRectangle);
}

