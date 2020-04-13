//
// Created by mathi on 4/8/2020.
//

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
                if(!createdTextures.count(path)){
                    createdTextures[path] = TextureManager::loadTexture(path);
                }
                directionTextures.emplace_back(createdTextures[path]);
            }
            textures.insert({key, directionTextures});
        }
    };

    std::map<Direction, std::vector<SDL_Texture *>> textures;
    std::map<const char *, SDL_Texture *> createdTextures;
    int frameCount = 0;
    int animationIndex = 0;

    void animate(SDL_Texture ** entityTexturePtr, Direction direction);
};


#endif //EXAM_ENTITYANIMATOR_H
