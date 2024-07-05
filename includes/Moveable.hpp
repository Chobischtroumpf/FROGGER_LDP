#pragma once

# include "Printable.hpp"

class Moveable: public virtual Printable{
public:
    virtual void keyPressed(int keyCode) = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
    virtual ~Moveable() = default;
};
