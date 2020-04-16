#include "../include/GameObject.h"
#include "../include/GameManager.h"

void GameObject::render() {
    SDLManager::render(m_texture, &m_sourceRectangle, &m_positionRectangle);
}
