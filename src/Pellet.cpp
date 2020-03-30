//
// Created by mathi on 3/25/2020.
//
#include <iostream>
#include "../include/Game.h"
#include "../include/Pellet.h"
#include "../include/Player.h"

void Pellet::update() {


    //Collision detection with player
    if(SDL_HasIntersection(&Game::getGameObjects()[0].get()->m_positionRectangle, &m_positionRectangle)) {
        SDL_DestroyTexture(texture);
        //TODO: Delete pellet from gameObjects
    }

}

std::string Pellet::getType() {
    return "Pellet";
}

