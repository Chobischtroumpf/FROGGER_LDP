#ifndef CANVAS_HPP
#define CANVAS_HPP 1

#include <vector>

class Canvas {
  std::vector<Cell> cc;

 public:
  Canvas();
  void draw();
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
};

#endif