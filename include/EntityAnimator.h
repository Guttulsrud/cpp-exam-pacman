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
            textures.insert({key, directionTextures});
        }
    };

    std::map<Direction, std::vector<SDL_Texture *>> textures;
    int frameCount = 0;
    int animationIndex = 0;

    void animate(SDL_Texture ** entityTexturePtr, Direction direction);
};


#endif