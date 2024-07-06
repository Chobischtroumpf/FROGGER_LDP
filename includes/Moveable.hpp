#pragma once
# include "Drawable.hpp"

namespace frogger {
  // The Moveable class is an abstract class that represents an object that can be moved.
  class Moveable: public virtual Drawable{
    public:
      virtual void keyPressed(int keyCode) = 0;
      virtual void moveLeft() = 0;
      virtual void moveRight() = 0;
      virtual void moveUp() = 0;
      virtual void moveDown() = 0;
      virtual ~Moveable() = default;
  };
}