#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

// ---------- Interface  ---------- //
class Component {
public:
    virtual ~Component() = default;

    virtual std::string getOwnerId() = 0;




};

#endif //COMPONENT_H
