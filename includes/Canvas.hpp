#ifndef CANVAS_HPP
#define CANVAS_HPP 1

#include <vector>
#include "Cell.hpp"
#include "Rectangle.hpp"
#include "Animation.hpp"

class Canvas {
  std::vector<Cell<Rectangle>> cc;

 public:
  Canvas();
  void draw();
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
};

#endif