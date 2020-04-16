#include "../include/Movable.h"



void Movable::updateHitBox() {
    hitBox.x = m_positionRectangle.x+20;
    hitBox.y = m_positionRectangle.y+20;

void Movable::moveInBoundsIfOutOfBounds() {
    if (m_positionRectangle.x > 892) {
        m_positionRectangle.x = -21;

    } else if (m_positionRectangle.x < -22) {
        m_positionRectangle.x = 891;
    }

    if (m_positionRectangle.y > 960) {
        m_positionRectangle.y = -21;

    } else if (m_positionRectangle.y < -22) {
        m_positionRectangle.y = 960;
    }
}
