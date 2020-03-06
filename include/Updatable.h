#ifndef UPDATABLE_H
#define UPDATABLE_H

// ---------- Interface  ---------- //
class Updatable {
public:
    virtual ~Updatable() = default;

    virtual void update() = 0;


};


#endif
