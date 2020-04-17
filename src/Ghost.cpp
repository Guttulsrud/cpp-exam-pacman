#include <map>
#include <random>
#include "../include/Ghost.h"
#include "../include/GameManager.h"


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

    std::map<Direction, SDL_Rect> directions = getDirectionsMap();
    std::map<Direction, SDL_Rect> possibleDirections;
    std::vector<Direction> possibleDirectionsVector;

    updateValidMoves(directions, possibleDirections, possibleDirectionsVector);

    if (possibleDirections.empty()) {
        direction = getOppositeDirection(direction);
        m_positionRectangle = directions[direction];
        return;
    }

    decideMove(directions, possibleDirections, possibleDirectionsVector);

    maintainPositionRelativeToTiles();
    prevDirections = possibleDirectionsVector;
    updateHitBox();
    animateState();
    moveInBoundsIfOutOfBounds();
}

void Ghost::maintainPositionRelativeToTiles() {
    while (m_positionRectangle.x % m_movementSpeed) {
        m_positionRectangle.x++;
    }
    while (m_positionRectangle.y % m_movementSpeed) {
        m_positionRectangle.y++;
    }
}

void Ghost::animateState() {
    if (dead) {
        deadAnimator.animate(&m_texture, direction);
    } else if (eatableStateEnd) {
        powerPelletStateEndAnimator.animate(&m_texture, direction);
    } else if (eatable) {
        powerPelletStateAnimator.animate(&m_texture, direction);
    } else {
        m_animator.animate(&m_texture, direction);
    }
}

void Ghost::decideMove(
        std::map<Direction, SDL_Rect> &directions,
        std::map<Direction, SDL_Rect> &possibleDirections,
        std::vector<Direction> &possibleDirectionsVector
) {

    if ((prevDirections != possibleDirectionsVector || possibleDirections.size() > 2)) {

        if (getRandomNumberInRange(0, 10) > difficulty && !dead) {
            auto item = possibleDirections.begin();
            std::advance(item, getRandomNumberInRange(0, possibleDirections.size() - 1));

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
            ghostReviveTimer = SDL_AddTimer(eatableTime + 2000, &Ghost::reviveGhostCallback, this);
        }
        m_positionRectangle = directions[direction];
    }
}

void Ghost::updateValidMoves(std::map<Direction, SDL_Rect> &directions,
                             std::map<Direction, SDL_Rect> &possibleDirections,
                             std::vector<Direction> &possibleDirectionsVector) {
    for (auto &directionPosition : directions) {
        bool didNotCollideWithWall = true;
        for (auto &object : GameManager::getStationery()) {
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
}

int Ghost::getRandomNumberInRange(int begin, int end) {
    static std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(begin, end);
    return dist(mt);
}

Direction Ghost::getDirectionToPoint(std::map<Direction, SDL_Rect> &possibleDirections) {

    Direction destination = UP;
    float shortestLength = 1000.0f;
    float longestLength = 0.0f;

    auto playerPos = GameManager::getPlayer()->m_positionRectangle;

    for (auto &directionPosition : possibleDirections) {
        int xLen;
        int yLen;
        if (dead) {
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
    m_movementSpeed = 3;
    Mix_HaltChannel(6);
    m_positionRectangle.x = spawn.x;
    m_positionRectangle.y = spawn.y;
    dead = false;
    eatableStateEnd = false;
    eatable = false;
    updateHitBox();
    eatable = false;
    direction = RIGHT;
    m_animator.animate(&m_texture, direction);
}

Uint32 Ghost::eatableStateEndCallback(Uint32 n, void *ghost) {
    auto *g = reinterpret_cast<Ghost *>(ghost);
    if (!g->dead && g->eatable)
        g->eatableStateEnd = true;
    return 0;
}

Uint32 Ghost::reviveGhostCallback(Uint32 n, void *ghost) {
    auto *g = reinterpret_cast<Ghost *>(ghost);
    if (!g->dead && g->eatable && g->eatableStateEnd) {
        g->eatableStateEnd = false;
        g->eatable = false;
        g->m_movementSpeed = 3;
    }
    return 0;
}

std::map<Direction, SDL_Rect> Ghost::getDirectionsMap() {

    SDL_Rect up = m_positionRectangle;
    up.y -= m_movementSpeed;
    SDL_Rect down = m_positionRectangle;
    down.y += m_movementSpeed;
    SDL_Rect left = m_positionRectangle;
    left.x -= m_movementSpeed;
    SDL_Rect right = m_positionRectangle;
    right.x += m_movementSpeed;

    return {{UP,    up},
            {DOWN,  down},
            {LEFT,  left},
            {RIGHT, right}};
}



