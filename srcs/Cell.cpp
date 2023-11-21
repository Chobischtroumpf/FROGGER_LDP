#include "Cell.hpp"

template <class Drawable>
Cell<Drawable>::Cell(Drawable drawable)
    : drawable{drawable} {}

template <class Drawable>
void Cell<Drawable>::draw() {
    drawable.draw();
}

template <class Drawable>
void Cell<Drawable>::mouseClick(Point mouseLoc) {
  if (drawable.contains(mouseLoc)) {
    drawable.setFillColow(FL_RED);
  } else {
    drawable.setFillColow(FL_WHITE);
  }
}

