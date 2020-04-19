#ifndef EXAM_ENTITYANIMATOR_H
#define EXAM_ENTITYANIMATOR_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include "GameObject.h"

class EntityAnimator {
public:
    EntityAnimator(std::map<Direction, std::vector<const char *>> paths){
        std::vector<SDL_Texture * > kek;
        for(auto const& [key, vec] : paths){
            std::vector<SDL_Texture *> directionTextures;
            for(auto &path : vec){
                directionTextures.emplace_back(TextureManager::loadTexture(path));
            }
            m_textures.insert({key, directionTextures});
        }
    };
    void animate(SDL_Texture ** entityTexturePtr, Direction direction);

private:

    std::map<Direction, std::vector<SDL_Texture *>> m_textures;
    int m_frameCount = 0;
    int m_animationIndex = 0;

};


#endif