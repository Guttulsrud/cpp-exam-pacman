//
// Created by marti on 30/03/2020.
//

#include "../include/VoidWarp.h"
#include "../include/Game.h"

void VoidWarp::update() {


    //Player collides with VoidWarp
    if(SDL_HasIntersection(&Game::getGameObjects()[0].get()->m_positionRectangle, &m_positionRectangle)) {

        if(m_side == 0) {

        }
        Game::getGameObjects()[0].get()->m_positionRectangle.x = 50;
    }

}

std::string VoidWarp::getType() {
    return "VoidWarp";
}