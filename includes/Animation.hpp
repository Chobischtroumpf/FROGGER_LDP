#pragma once

#include <FL/fl_draw.H>
#include "Point.hpp"

namespace frogger {

  struct Translation {
    explicit Translation(Point p) {
      fl_push_matrix();
      fl_translate(p.x, p.y);
    }
    ~Translation() { fl_pop_matrix(); }
  };

  struct Rotation {
    explicit Rotation(double angle) {
      fl_push_matrix();
      fl_rotate(angle);
    }
    ~Rotation() { fl_pop_matrix(); }
  };

} // namespace frogger
