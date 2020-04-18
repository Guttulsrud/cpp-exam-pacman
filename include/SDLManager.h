#ifndef EXAM_SDLMANAGER_H
#define EXAM_SDLMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "../utils/SDL_FontCache.h"
#include "GameObject.h"

enum class Sound {
    EAT_PELLET, EAT_POWER_PELLET, DEATH, EAT_FRUIT, EAT_GHOST, INTRO, MAP_COMPLETED, GHOST_RETURN
};

class SDLManager {
public:
    static SDLManager &getInstance() {
        static SDLManager instance;
        return instance;
    }

    int init(const char *title, int x, int y, int w, int h);

    void clean();

    void initSounds();

    void playSound(Sound sound, int channel = -1);

    void stopSoundOnChannel(int channel);

    void stopExecutionWhileSoundPlaying(int channel);

    void renderBuffer();

    void drawText(const char *text, float x, float y, int parameter = 0);

    void setFontSize(int size);

    void showReadyText();

    void render(SDL_Texture *texture, const SDL_Rect *src, const SDL_Rect *dest);

    void renderStartScreen();

    static SDL_Renderer *m_renderer;

    std::map<Sound, Mix_Chunk *> m_sounds;

private:

    FC_Font *m_font;

    SDLManager() = default;

    SDL_Window *m_window;

};


#endif
