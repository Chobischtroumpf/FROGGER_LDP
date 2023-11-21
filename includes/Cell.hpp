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
#endif