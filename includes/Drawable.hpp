#pragma once

namespace frogger {
  // The Drawable class is an abstract class that represents an object that can be drawn.
  class Drawable {
    public:
      virtual void draw() = 0;
      virtual ~Drawable() = default;
  };
} // namespace frogger
