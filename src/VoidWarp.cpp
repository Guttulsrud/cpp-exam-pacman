#include "../include/VoidWarp.h"
#include "../include/Game.h"

void VoidWarp::update() {


    //Player or ghost collides with VoidWarp
    for (auto &object : Game::getGameObjects()) {
        if (object->getType() == PLAYER || object->getType() == GHOST) {
            if (SDL_HasIntersection(&object->m_positionRectangle, &m_positionRectangle)) {
                if (m_side == 1) {
                    object->m_positionRectangle.x = -20;
                } else if (m_side == 0) {
                    object->m_positionRectangle.x = 860;
                }
            }
        }
    }

}

TYPE VoidWarp::getType() {
    return VOIDWARP;
}