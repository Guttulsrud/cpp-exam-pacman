#include <iostream>
#include "../include/SDLManager.h"
#include "../include/TextureManager.h"


SDL_Renderer *SDLManager::m_renderer = nullptr;

int SDLManager::init(const char *title, int xPos, int yPos, int width, int height) {

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
        m_window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if (!m_window) {
            std::cout << "Couldn't open Window!" << std::endl;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, flags);

        if (m_renderer) {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        } else {
            std::cout << "Couldn't create renderer" << std::endl;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)) {
            Mix_AllocateChannels(8);
        }

        if (TTF_Init() != 0) {
            std::cout << "Couldn't open TTF" << std::endl;
        }
    }
    return 0;
}


void SDLManager::clean() {
    TTF_Quit();
    FC_FreeFont(m_font);
    Mix_CloseAudio();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLManager::initFonts() {
    setFontSize(42);
    drawText("Ready!", 400, 545);
    setFontSize(24);
}

void SDLManager::drawText(const char *text, float x, float y, int parameter) {
    FC_Draw(m_font, m_renderer, x, y, text, parameter);
}

void SDLManager::setFontSize(int size) {
    m_font = FC_CreateFont();
    FC_LoadFont(m_font, m_renderer, "../resources/fonts/arial.ttf", size, FC_MakeColor(255, 255, 0, 255), TTF_STYLE_NORMAL);
}

void SDLManager::renderBuffer() {
    SDL_RenderPresent(m_renderer);
    SDL_RenderClear(m_renderer);
}

void SDLManager::render(SDL_Texture *texture, const SDL_Rect *src, const SDL_Rect *dest) {
    SDL_RenderCopy(m_renderer, texture, src, dest);
}


void SDLManager::renderStartScreen() {
    auto startScreenRect = SDL_Rect{0, 0, 930, 1020};

    render( TextureManager::loadTexture(
            "../resources/startscreenassets/start_screen.png"), &startScreenRect, &startScreenRect);

    m_font = FC_CreateFont();
    FC_LoadFont(m_font, m_renderer, "../resources/fonts/arial.ttf", 30, FC_MakeColor(240, 153, 63, 255), TTF_STYLE_BOLD);
    FC_Draw(m_font, m_renderer, 295, 380, "Press Space to start!");
    FC_Draw(m_font, m_renderer, 330, 550, "Press 'Q' to quit!");

    FC_FreeFont(m_font);

    SDL_RenderPresent(m_renderer);
    SDL_RenderClear(m_renderer);
}
