#ifndef CHARACTER_H
#define CHARACTER_H


#include <string>
#include <vector>
#include "Updatable.h"
#include "Component.h"

class Character: Updatable {

public:
    void update() override;

    std::string name;
    int id;
    std::vector<Component> components;
};


#endif // CHARACTER_H
