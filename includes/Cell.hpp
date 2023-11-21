#ifndef CELL_HPP
#define CELL_HPP 1

#include "Rectangle.hpp"

template <typename Drawable>
class Cell {
  Drawable   drawable;

 public:
  // Constructor
  Cell(Drawable drawable);

  // Methods that draw and handle events
  void draw();
  void mouseClick(Point mouseLoc);

  ~Cell() {}
};

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
    drawable.setFillColor(FL_RED);
  } else {
    drawable.setFillColor(FL_WHITE);
  }
}

#endif