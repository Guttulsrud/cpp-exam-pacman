#include <cstring>
#include <iostream>
#include "../include/InputManager.h"

bool InputManager::KeyDown(int iKeyIndex) {
    return !oldKeys[iKeyIndex] && keys[iKeyIndex];
}

bool InputManager::KeyStillDown(int iKeyIndex) {
    return oldKeys[iKeyIndex] && keys[iKeyIndex];
}

bool InputManager::KeyUp(int iKeyIndex) {
    return oldKeys[iKeyIndex] && !keys[iKeyIndex];
}

bool InputManager::KeyStillUp(int iKeyIndex) {
    return !(oldKeys[iKeyIndex] && keys[iKeyIndex]);
}

InputManager &InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::update() {
    m_oldMouseButtons = m_mouseButtons;
    memcpy(oldKeys, keys, keyCount * sizeof(Uint8));
    SDL_PumpEvents();
    m_mouseButtons = SDL_GetRelativeMouseState(&mouseX, &mouseY);

}
