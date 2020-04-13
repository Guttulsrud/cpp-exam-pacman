//
// Created by marti on 08/04/2020.
//

#include "../include/Fruit.h"



TYPE Fruit::getType() {
    return FRUIT;
}

void Fruit::update() {
   // fruitSpawnTimer = SDL_AddTimer(5000, &Fruit::fruitSpawnCallback, this);
}

/*
Uint32 Fruit::fruitSpawnCallback(Uint32 n, void *fruit) {
    auto *f = reinterpret_cast<Fruit *>(fruit);
    f->m_active = true;
    return 0;
}
*/