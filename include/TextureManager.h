#ifndef EXAM_TEXTUREMANAGER_H
#define EXAM_TEXTUREMANAGER_H


#include <SDL2/SDL.h>
#include <map>

class TextureManager {
public:

    static SDL_Texture *loadTexture(const std::string& path);

private:

    static std::map<std::string, SDL_Texture *> m_createdTextures;

};

#endif
