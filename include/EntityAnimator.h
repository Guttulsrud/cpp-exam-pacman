//
// Created by mathi on 4/8/2020.
//

#ifndef EXAM_ENTITYANIMATOR_H
#define EXAM_ENTITYANIMATOR_H


#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "GameObject.h"

class EntityAnimator {
public:
    EntityAnimator(std::map<Direction, std::vector<const char *>> paths){
        std::vector<SDL_Texture * > kek;
        for(auto const& [key, vec] : paths){
            int len = vec.size();
            std::vector<SDL_Texture *> temp;
            for(int i = 0; i < len; i++){
                temp.emplace_back(TextureManager::loadTexture(vec[i]));
            }
            textures.insert({key, temp});
        }
    };
    std::map<Direction, std::vector<SDL_Texture *>> textures;
    int frameCount = 0;
    int animationIndex = 0;

    void animate(SDL_Texture ** entityTexturePtr, Direction direction);
};


#endif //EXAM_ENTITYANIMATOR_H
