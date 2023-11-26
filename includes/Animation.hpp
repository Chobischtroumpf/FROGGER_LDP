#ifndef __ANIMATION_HPP
#define __ANIMATION_HPP

#include "Froggers.hpp"
#include "Point.hpp"

struct Translation {
  explicit Translation(Point p) {
    fl_push_matrix();
    fl_translate(p.x, p.y);
  }
  ~Translation() { fl_pop_matrix(); }
};

#endif //!__ANIMATION_HPP