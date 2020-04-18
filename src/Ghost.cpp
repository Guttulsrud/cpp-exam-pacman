#include <map>
#include <random>
#include "../include/Ghost.h"
#include "../include/GameManager.h"


Direction getOppositeDirection(Direction direction) {
    switch (direction) {
        case Direction::UP:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::LEFT;
        default:
            return Direction::UP;
    }
}

void Ghost::update() {

    std::map<Direction, SDL_Rect> directions = getDirectionsMap();
    std::map<Direction, SDL_Rect> possibleDirections;
    std::vector<Direction> possibleDirectionsVector;

    updateValidMoves(directions, possibleDirections, possibleDirectionsVector);

    if (possibleDirections.empty()) {
        m_direction = getOppositeDirection(m_direction);
        m_positionRectangle = directions[m_direction];
        return;
    }

    decideMove(directions, possibleDirections, possibleDirectionsVector);

    if(m_dead && SDL_HasIntersection(&m_respawnPoint, &m_positionRectangle)){
        reset();
    }

    maintainPositionRelativeToTiles();
    m_prevDirections = possibleDirectionsVector;
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
    if (m_dead) {
        deadAnimator.animate(&m_texture, m_direction);
    } else if (m_eatableStateEnd) {
        powerPelletStateEndAnimator.animate(&m_texture, m_direction);
    } else if (m_eatable) {
        powerPelletStateAnimator.animate(&m_texture, m_direction);
    } else {
        m_animator.animate(&m_texture, m_direction);
    }
}

void Ghost::decideMove(
        std::map<Direction, SDL_Rect> &directions,
        std::map<Direction, SDL_Rect> &possibleDirections,
        std::vector<Direction> &possibleDirectionsVector
) {

    if ((m_prevDirections != possibleDirectionsVector )) {
        if (getRandomNumberInRange(0, 10) > m_difficulty && !m_dead) {
            auto item = possibleDirections.begin();
            std::advance(item, getRandomNumberInRange(0, possibleDirections.size() - 1));

            m_direction = item->first;
            m_positionRectangle = item->second;
        } else {
            Direction closestToDestination = getDirectionToPoint(possibleDirections);
            m_direction = closestToDestination;
            m_positionRectangle = possibleDirections[closestToDestination];
        }
    } else {
        if (m_switchedToEatable) {
            m_direction = getDirectionToPoint(directions);
            m_eatable = true;
            m_switchedToEatable = false;

            SDL_RemoveTimer(m_eatableStateEndTimer);
            SDL_RemoveTimer(m_ghostReviveTimer);
            int eatableTime = 7000;

            m_eatableStateEndTimer = SDL_AddTimer(eatableTime, &Ghost::eatableStateEndCallback, this);
            m_ghostReviveTimer = SDL_AddTimer(eatableTime + 2000, &Ghost::reviveGhostCallback, this);
        }
        m_positionRectangle = directions[m_direction];
    }
}

void Ghost::updateValidMoves(std::map<Direction, SDL_Rect> &directions,
                             std::map<Direction, SDL_Rect> &possibleDirections,
                             std::vector<Direction> &possibleDirectionsVector) const {
    for (auto &directionPosition : directions) {
        bool didNotCollideWithWall = true;
        for (auto &object : GameManager::getStationery()) {
            if (object->getType() == TYPE::WALL) {
                if (SDL_HasIntersection(&directionPosition.second, &object->m_positionRectangle)) {
                    didNotCollideWithWall = false;
                }
            }
        }
        if (didNotCollideWithWall && directionPosition.first != getOppositeDirection(m_direction)) {
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

Direction Ghost::getDirectionToPoint(std::map<Direction, SDL_Rect> &possibleDirections) const {

    Direction destination = Direction::UP;
    float shortestLength = 1000.0f;
    float longestLength = 0.0f;

    auto playerPos = GameManager::getPlayer()->m_positionRectangle;

    for (auto &directionPosition : possibleDirections) {
        int xLen;
        int yLen;
        if (m_dead) {
            xLen = abs(m_respawnPoint.x - directionPosition.second.x);
            yLen = abs(m_respawnPoint.y - directionPosition.second.y);
        } else {
            xLen = abs(playerPos.x - directionPosition.second.x);
            yLen = abs(playerPos.y - directionPosition.second.y);
        }
        float lenToDestination = sqrt((xLen * xLen) + (yLen * yLen));

        if ((m_eatable || m_switchedToEatable) && !m_dead) {
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
    m_positionRectangle.x = m_spawn.x;
    m_positionRectangle.y = m_spawn.y;
    m_dead = false;
    m_eatableStateEnd = false;
    m_eatable = false;
    updateHitBox();
    m_direction = Direction::RIGHT;
    m_animator.animate(&m_texture, m_direction);
}

Uint32 Ghost::eatableStateEndCallback(Uint32 n, void *ghost) {
    //Jeg ønsket å være konsistent og bruke SDL ting til å løse mest mulig av oppgaven.
    //Jeg ble nødt til å bruke reintepret_cast siden en SDL timercallback krever en void peker
    //Det vil aldri være et tilfelle hvor denne metoden blir kalt, uten at "void * ghost" peker på et Ghost object
    auto *g = reinterpret_cast<Ghost *>(ghost);
    if (!g->m_dead && g->m_eatable)
        g->m_eatableStateEnd = true;
    return 0;
}

Uint32 Ghost::reviveGhostCallback(Uint32 n, void *ghost) {
    //Jeg ønsket å være konsistent og bruke SDL ting til å løse mest mulig av oppgaven.
    //Jeg ble nødt til å bruke reintepret_cast siden en SDL timercallback krever en void peker
    //Det vil aldri være et tilfelle hvor denne metoden blir kalt, uten at "void * ghost" peker på et Ghost object
    auto *g = reinterpret_cast<Ghost *>(ghost);
    if (!g->m_dead && g->m_eatable && g->m_eatableStateEnd) {
        g->m_eatableStateEnd = false;
        g->m_eatable = false;
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

    return {{Direction::UP,    up},
            {Direction::DOWN,  down},
            {Direction::LEFT,  left},
            {Direction::RIGHT, right}};
}

void Ghost::powerPelletState() {
    if(m_dead)
        return;
    m_switchedToEatable = true;
    m_eatableStateEnd = false;
    m_movementSpeed = 2;
}

void Ghost::die() {
    m_movementSpeed = 5;
    m_dead = true;
    m_eatable = false;
    m_switchedToEatable = false;
}



