#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <memory>

class InputManager {
public:

    InputManager() {
        m_keys = SDL_GetKeyboardState(&m_keyCount);
        m_oldKeys = new Uint8[m_keyCount];
    }

    void update();

    static InputManager &getInstance();

    bool keyDown(int iKeyIndex);

    bool keyStillDown(int iKeyIndex);

    bool keyUp(int iKeyIndex);

    bool keyStillUp(int iKeyIndex);


protected:
    const Uint8 *m_keys;
    Uint8 *m_oldKeys;
    int m_keyCount;
};


#endif
