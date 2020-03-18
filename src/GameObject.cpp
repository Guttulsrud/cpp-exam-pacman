
#include <iostream>
#include "../include/GameObject.h"
#include "../include/Game.h"
#include "../include/InputManager.h"


GameObject::GameObject(const char *textureSheet, int w, int h, int x, int y, int id, bool isAi) {

    objTexture = Game::loadTexture(textureSheet);
    m_position.x = x;
    m_position.y = y;
    m_width = w;
    m_height = h;
    m_destination = m_position;
    m_ai = isAi;
    m_id = id;

}

void GameObject::aiFollow() {
    if (abs(m_destination.x - m_position.x) < moveSpeed) {
        m_position.x = m_destination.x;
    } else if (m_destination.x > m_position.x) {
        m_position.x += moveSpeed;
    } else if (m_destination.x < m_position.x) {
        m_position.x -= moveSpeed;
    }

    if (abs(m_destination.y - m_position.y) < moveSpeed) {
        m_position.y = m_destination.y;
    } else if (m_destination.y > m_position.y) {
        m_position.y += moveSpeed;
    } else if (m_destination.y < m_position.y) {
        m_position.y -= moveSpeed;
    }
}

void GameObject::update() {

    if (m_ai) {
        aiFollow();
    } else {
        moveSpeed = 10;
        if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_W)) {
            m_position.y -= moveSpeed;
        }
        if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_A)) {
            m_position.x -= moveSpeed;
        }
        if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_S)) {
            m_position.y += moveSpeed;
        }
        if (InputManager::getInstance().KeyStillDown(SDL_SCANCODE_D)) {
            m_position.x += moveSpeed;
        }
    }

    srcRect.h = m_height;
    srcRect.w = m_width;
    srcRect.x = m_position.x;
    srcRect.y = m_position.y;

    bool collided = false;
    std::for_each(std::begin(Game::getGameObjects()), std::end(Game::getGameObjects()),
                  [this, &collided](std::shared_ptr<GameObject> &object) {
                      if (m_id != object->m_id) {
                          if (SDL_HasIntersection(&srcRect, &object->srcRect)) {
                              collided = true;
                          }
                      }
                  });

    if (!collided) {
        destRect.x = m_position.x;
        destRect.y = m_position.y;
        destRect.w = srcRect.w;
        destRect.h = srcRect.h;
    } else {
        m_position.x = destRect.x;
        m_position.y = destRect.y;
    }
}


void GameObject::setDestination(int x, int y) {
    m_destination.x = x;
    m_destination.y = y;
}


void GameObject::render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}


GameObject::~GameObject() {

}
