#ifndef DRAWABLE2D_H
#define DRAWABLE2D_H

// ---------- Interface  ---------- //
class Drawable2D {
public:
    virtual ~Drawable2D() = default;

    virtual void getImage() = 0;

    virtual void getPosition() = 0;

    virtual int getHeight() = 0;

    virtual int getWidth() = 0;


};


#endif //DRAWABLE2D_H
