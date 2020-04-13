#include "../include/EntityAnimator.h"
#include "../include/GameManager.h"

void EntityAnimator::animate(SDL_Texture **entityTexturePtr, Direction direction) {

    if (direction == NONE) {
        GameManager::getPlayer()->m_texture = textures[UP][0];
        return;
    }
    if (frameCount == 5) {
        animationIndex++;
        frameCount = 0;
    }
    if (animationIndex == textures[direction].size()) {
        animationIndex = 0;
    }

    *entityTexturePtr = textures[direction][animationIndex];
    frameCount++;
}
