//
// Created by mathi on 4/8/2020.
//

#include "../include/EntityAnimator.h"
#include "../include/Game.h"

void EntityAnimator::animate() {
    Direction playerDirection = Game::getPlayer()->direction;
    if(playerDirection == NONE){
        Game::getPlayer()->m_texture = textures[UP][0];
        std::cout << "LEL" << std::endl;
        return;
    }

    if(frameCount<10) animationIndex = 0;
    else if(frameCount<20) animationIndex = 1;
    else if(frameCount<30) animationIndex = 2;
    else if(frameCount>30) frameCount = 0;

    Game::getPlayer()->m_texture = textures[playerDirection][animationIndex];

    frameCount++;
}
