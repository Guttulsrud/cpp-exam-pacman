//
// Created by mathi on 3/31/2020.
//

#include <iostream>
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

    std::cout << " | " << possibleDirections.size() << std::endl;


    //En intersection er en sving og et kryss
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


