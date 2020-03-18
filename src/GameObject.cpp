
#include <iostream>
#include "../include/GameObject.h"
#include "../include/Game.h"
#include "../include/InputManager.h"


GameObject::GameObject(const char *textureSheet, int x, int y, int id) {

    objTexture = Game::loadTexture(textureSheet);
    m_position.x = x;
    m_position.y = y;
    m_destination = m_position;
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

//    if (m_ai) {
//       aiFollow();
//    } else {
    moveSpeed = 7;
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
//        }


    }

    srcRect.h = 32;
    srcRect.w = 32;

    srcRect.x = m_position.x;
    srcRect.y = m_position.y;

    // check collide here


    std::for_each(std::begin(Game::getGameObjects()), std::end(Game::getGameObjects()),
                  [](std::shared_ptr<GameObject> &object) {
                      std::cout << object->m_id << std::endl;
                  });


//    for(auto &o : gameObjects) {
//        std::cout << o.m_id << std::endl;
//
//        if(SDL_HasIntersection(&srcRect, &o.srcRect)){
//            std::cout << o.m_id << " collided with " << m_id << std::endl;
//        }
//    }

    destRect.x = m_position.x;
    destRect.y = m_position.y;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
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
