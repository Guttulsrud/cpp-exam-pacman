#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <memory>

class InputManager {
public:

    InputManager() {
        keys = SDL_GetKeyboardState(&keyCount);
        oldKeys = new Uint8[keyCount];
    }

    void update();

    static InputManager &getInstance();

    bool KeyDown(int iKeyIndex);

    bool KeyStillDown(int iKeyIndex);

    bool KeyUp(int iKeyIndex);

    bool KeyStillUp(int iKeyIndex);


protected:
    const Uint8 *keys;
    Uint8 *oldKeys;
    int keyCount;
};


#endif
