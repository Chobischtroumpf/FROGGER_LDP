#ifndef __CANVAS_HPP
#define __CANVAS_HPP

#include <vector>
#include "Cell.hpp"
#include "Frog.hpp"


class Canvas {
  std::vector<std::vector<Cell<Rectangle>>> cc;
  Frog frog;

 public:
  Canvas();
  void draw();
  // void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
};

#endif //!__CANVAS_HPP