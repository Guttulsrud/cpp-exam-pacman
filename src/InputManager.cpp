#include "../include/InputManager.h"

bool InputManager::keyDown(int iKeyIndex) {
    return !m_oldKeys[iKeyIndex] && m_keys[iKeyIndex];
}

bool InputManager::keyStillDown(int iKeyIndex) {
    return m_oldKeys[iKeyIndex] && m_keys[iKeyIndex];
}

bool InputManager::keyUp(int iKeyIndex) {
    return m_oldKeys[iKeyIndex] && !m_keys[iKeyIndex];
}

bool InputManager::keyStillUp(int iKeyIndex) {
    return !(m_oldKeys[iKeyIndex] && m_keys[iKeyIndex]);
}

InputManager &InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::update() {
    memcpy(m_oldKeys, m_keys, m_keyCount * sizeof(Uint8));
    SDL_PumpEvents();
}

