//
// Created by mathi on 3/31/2020.
//

#include <iostream>
#include <map>
#include "../include/Ghost.h"
#include "../include/Game.h"

std::string Ghost::getType() {
    return "Ghost";
}

void Ghost::update() {


    std::map<Direction, SDL_Rect> positions;

    SDL_Rect temp = m_positionRectangle;
    temp.y -= 1;
    positions.insert({UP, temp});
    temp = m_positionRectangle;
    temp.y += 1;
    positions.insert({DOWN, temp});
    temp = m_positionRectangle;
    temp.x -= 1;
    positions.insert({LEFT, temp});
    temp = m_positionRectangle;
    temp.x += 1;
    positions.insert({RIGHT, temp});

    std::map<Direction, SDL_Rect> possibleDirections;
    std::vector<Direction> possibleDirectionsVector;

    int totalPossibleDirections = 0;
    for (auto &directionPosition : positions) {
        bool didNotCollideWithWall = true;
        for (auto &object : Game::getGameObjects()) {
            if (object->getType() == "Wall") {
                if (SDL_HasIntersection(&directionPosition.second, &object->m_positionRectangle)) {
                    didNotCollideWithWall = false;
                }
            }
        }
        if (didNotCollideWithWall) {
            totalPossibleDirections++;
            possibleDirections.insert(directionPosition);
            possibleDirectionsVector.push_back(directionPosition.first);
        }
    }

    std::cout << "Can move: ";
    for (auto d : possibleDirections) {
        switch (d.first) {
            case UP:
                std::cout << "UP ";
                break;
            case DOWN:
                std::cout << "DOWN ";
                break;
            case LEFT:
                std::cout << "LEFT ";
                break;
            case RIGHT:
                std::cout << "RIGHT ";
                break;
        }
    }


    std::cout << " | " << totalPossibleDirections << std::endl;

    if (prevDirections == possibleDirectionsVector) {
        m_positionRectangle = positions[direction];
    } else {
        auto item = possibleDirections.begin();
        srand(48);
        std::advance(item, rand() % totalPossibleDirections);
        direction = item->first;
        m_positionRectangle = item->second;
    }

    prevDirections = possibleDirectionsVector;

}


