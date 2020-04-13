#include <map>
#include <random>
#include "../include/Ghost.h"
#include "../include/Game.h"

TYPE Ghost::getType() {
    return GHOST;
}

Direction getOppositeDirection(Direction direction) {
    switch (direction) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        default:
            return UP;
    }
}

void Ghost::update() {
    std::map<Direction, SDL_Rect> directions;

    //NEW VOIDWARP
    //TODO: put voidwarp in method
    if(m_positionRectangle.x > 892){
        m_positionRectangle.x = -21;

    } else if(m_positionRectangle.x < -22){
        m_positionRectangle.x = 891;
    }

    if (m_positionRectangle.y > 960) {
        m_positionRectangle.y = -21;

    } else if (m_positionRectangle.y < -22) {
        m_positionRectangle.y = 960;
    }


    SDL_Rect temp = m_positionRectangle;
    temp.y -= m_movementSpeed;
    directions.insert({UP, temp});
    temp = m_positionRectangle;
    temp.y += m_movementSpeed;
    directions.insert({DOWN, temp});
    temp = m_positionRectangle;
    temp.x -= m_movementSpeed;
    directions.insert({LEFT, temp});
    temp = m_positionRectangle;
    temp.x += m_movementSpeed;
    directions.insert({RIGHT, temp});

    std::map<Direction, SDL_Rect> possibleDirections;
    std::vector<Direction> possibleDirectionsVector;

    //Finds valid move direction
    for (auto &directionPosition : directions) {
        bool didNotCollideWithWall = true;
        for (auto &object : Game::getStationaryGameObjects()) {
            if (object->getType() == WALL) {
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

    if (possibleDirections.empty()) {
        direction = getOppositeDirection(direction);
        m_positionRectangle = directions[direction];
        return;
    }

    //decides which way
    if ((prevDirections != possibleDirectionsVector || possibleDirections.size() > 2)) {

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, 10);

        if (dist(mt) > difficulty && !dead) {

            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(0, possibleDirections.size() - 1);

            auto item = possibleDirections.begin();
            std::advance(item, dist(mt));

            direction = item->first;
            m_positionRectangle = item->second;
        } else {
            Direction closestToDestination = getDirectionToPoint(possibleDirections);
            direction = closestToDestination;
            m_positionRectangle = possibleDirections[closestToDestination];
        }
    } else {
        if (switchedToEatable) {
            direction = getDirectionToPoint(directions);
            eatable = true;
            switchedToEatable = false;

            SDL_RemoveTimer(eatableStateEndTimer);
            SDL_RemoveTimer(ghostReviveTimer);
            int eatableTime = 7000;

            eatableStateEndTimer = SDL_AddTimer(eatableTime, &Ghost::eatableStateEndCallback, this);
            ghostReviveTimer = SDL_AddTimer(eatableTime+2000, &Ghost::reviveGhostCallback, this);
        }
        m_positionRectangle = directions[direction];
    }

    prevDirections = possibleDirectionsVector;
    updateHitbox();
    if (dead) {
        deadAnimator.animate(&m_texture, direction);
    } else if (eatableStateEnd) {
        powerPelletStateEndAnimator.animate(&m_texture, direction);
    } else if (eatable) {
        powerPelletStateAnimator.animate(&m_texture, direction);
    } else {
        m_animator.animate(&m_texture, direction);
    }

    if(m_positionRectangle.x == spawn.x && m_positionRectangle.y == spawn.y && dead){
        reset();
    }
}

Direction Ghost::getDirectionToPoint(const std::map<Direction, SDL_Rect> &possibleDirections) const {

    Direction destination = UP;
    float shortestLength = 1000.0f;
    float longestLength = 0.0f;

    auto playerPos = Game::getPlayer()->m_positionRectangle;

    for (auto &directionPosition : possibleDirections) {
        int xLen;
        int yLen;
        if(dead){
            xLen = abs(spawn.x - directionPosition.second.x);
            yLen = abs(spawn.y - directionPosition.second.y);
        } else {
            xLen = abs(playerPos.x - directionPosition.second.x);
            yLen = abs(playerPos.y - directionPosition.second.y);
        }
        float lenToDestination = sqrt((xLen * xLen) + (yLen * yLen));

        if ((eatable || switchedToEatable) && !dead) {
            if (lenToDestination > longestLength) {
                longestLength = lenToDestination;
                destination = directionPosition.first;
            }
        } else {
            if (lenToDestination < shortestLength) {
                shortestLength = lenToDestination;
                destination = directionPosition.first;
            }
        }
    }
    return destination;
}

void Ghost::reset() {
    m_positionRectangle.x = spawn.x;
    m_positionRectangle.y = spawn.y;
    dead = false;
    eatableStateEnd = false;
    eatable = false;
    updateHitbox();
    eatable = false;
    m_animator.animate(&m_texture, direction);
}

Uint32 Ghost::eatableStateEndCallback(Uint32 n, void *ghost) {
    auto *g = reinterpret_cast<Ghost *>(ghost);
    if(!g->dead && g->eatable)
        g->eatableStateEnd = true;
    return 0;
}

Uint32 Ghost::reviveGhostCallback(Uint32 n, void *ghost) {
    auto *g = reinterpret_cast<Ghost *>(ghost);
    if (!g->dead && g->eatable && g->eatableStateEnd) {
        g->eatableStateEnd = false;
        g->eatable = false;
    }
    return 0;
}



