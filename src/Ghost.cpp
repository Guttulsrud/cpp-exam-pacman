#include <map>
#include <random>
#include "../include/Ghost.h"
#include "../include/Game.h"

std::string Ghost::getType() {
    return "Ghost";
}

Direction getOppositeDirection(Direction direction){
    Direction returnDir;
    switch (direction) {
        case UP:
            returnDir = DOWN;
            break;
        case DOWN:
            returnDir = UP;
            break;
        case LEFT:
            returnDir = RIGHT;
            break;
        case RIGHT:
            returnDir = LEFT;
            break;
    }
    return returnDir;
}

void Ghost::update() {

    std::map<Direction, SDL_Rect> positions;

    SDL_Rect temp = m_positionRectangle;
    temp.y -= m_movementSpeed;
    positions.insert({UP, temp});
    temp = m_positionRectangle;
    temp.y += m_movementSpeed;
    positions.insert({DOWN, temp});
    temp = m_positionRectangle;
    temp.x -= m_movementSpeed;
    positions.insert({LEFT, temp});
    temp = m_positionRectangle;
    temp.x += m_movementSpeed;
    positions.insert({RIGHT, temp});

    std::map<Direction, SDL_Rect> possibleDirections;
    std::vector<Direction> possibleDirectionsVector;

    for (auto &directionPosition : positions) {
        bool didNotCollideWithWall = true;
        for (auto &object : Game::getGameObjects()) {
            if (object->getType() == "Wall") {
                if (SDL_HasIntersection(&directionPosition.second, &object->m_positionRectangle)) {
                    didNotCollideWithWall = false;
                }
            }
        }
        if (didNotCollideWithWall && directionPosition.first != getOppositeDirection(direction)) {
            possibleDirections.insert(directionPosition);
            possibleDirectionsVector.push_back(directionPosition.first);
        }
    }

    if ((prevDirections != possibleDirectionsVector || possibleDirections.size() > 2) && !wasAtIntersection){
        auto item = possibleDirections.begin();
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, possibleDirections.size()-1);
        std::advance(item, dist(mt));
        direction = item->first;
        m_positionRectangle = item->second;
        wasAtIntersection = true;
    } else {
        m_positionRectangle = positions[direction];
        wasAtIntersection = false;
    }

    prevDirections = possibleDirectionsVector;
}


