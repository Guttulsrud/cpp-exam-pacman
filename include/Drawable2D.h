#ifndef DRAWABLE2D_H
#define DRAWABLE2D_H

// ---------- Interface  ---------- //
class Drawable2D {
public:
    virtual ~Drawable2D() = default;

    virtual void getImage() = 0;

    virtual void getPosition() = 0;

    virtual void getHeight() = 0;

    virtual void getWidth() = 0;


};


#endif //DRAWABLE2D_H
