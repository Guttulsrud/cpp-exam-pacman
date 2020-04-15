//
// Created by mathi on 4/15/2020.
//

#ifndef EXAM_SDLMANAGER_H
#define EXAM_SDLMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "../utils/SDL_FontCache.h"

class SDLManager {
public:
    static SDLManager &getInstance() {
        static SDLManager instance;
        return instance;
    }
    static SDL_Renderer * m_renderer;
    int init(const char *title, int x, int y, int w, int h);
    void clean();
    void renderBuffer();

    void drawText(const char *text, float x, float y, int parameter = 0);

    void setFontSize(int size);

    void initFonts();

    void renderStartScreen();

private:

    FC_Font *font;

    SDLManager() = default;

    SDL_Window *window;

};


#endif //EXAM_SDLMANAGER_H