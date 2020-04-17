#include "../include/EntityAnimator.h"
#include "../include/GameManager.h"

void EntityAnimator::animate(SDL_Texture **entityTexturePtr, Direction direction) {

    if (direction == NONE) {
        GameManager::getPlayer()->m_texture = m_textures[UP][0];
        return;
    }
    if (m_frameCount == 5) {
        m_animationIndex++;
        m_frameCount = 0;
    }
    if (m_animationIndex == m_textures[direction].size()) {
        m_animationIndex = 0;
    }

    *entityTexturePtr = m_textures[direction][m_animationIndex];
    m_frameCount++;
}
