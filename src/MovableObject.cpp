//
// Created by Halo_ on 05.04.2020.
//

#include "../include/MovableObject.h"
#include "../include/GameManager.h"


void MovableObject::updateHitbox() {
    hitbox.x = m_positionRectangle.x;
    hitbox.y = m_positionRectangle.y;
}
