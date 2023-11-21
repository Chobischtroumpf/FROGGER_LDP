#include "froggers.hpp"
#include "Point.hpp"

struct Translation {
  explicit Translation(Point p) {
    fl_push_matrix();
    fl_translate(p.x, p.y);
  }
  ~Translation() { fl_pop_matrix(); }
};