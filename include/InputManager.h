#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#ifdef WIN32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>

#endif
#include <SDL_quit.h>
#include <memory>

class InputManager {
public:

    InputManager() {
        //keys = SDL_GetKeyboardState(keyCount);

        oldKeys = std::unique_ptr<Uint8>(new Uint8[keyCount]);
    }

    void update();

    static InputManager &getInstance();

    // Keyboard.
    bool KeyDown(int iKeyIndex);

    bool KeyStillDown(int iKeyIndex);

    bool KeyUp(int iKeyIndex);

    bool KeyStillUp(int iKeyIndex);


    // Mouse.
    bool MouseDown(int iButton);

    bool MouseStillDown(int iButton);

    bool MouseUp(int iButton);

    bool MouseStillUp(int iButton);

protected:

    // A pointer to SDL's internal key state array.
    // (Memory handled by SDL.)
    Uint8 *keys;
    // Our own copy of last update's array.
    // NB! Memory handled dynamically by us!
    std::unique_ptr<Uint8> oldKeys; // Number of keys in the arrays above, for this
    // app. (Can vary depending on setup/hardware.)
    int keyCount;

    // Mouse pos x and y.
    int mouseX;
    int mouseY;
    // Mouse buttons pressed.
    Uint8 m_mouseButtons;
    // Mouse buttons pressed last update.
    Uint8 m_oldMouseButtons;


};


#endif
