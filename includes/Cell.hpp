#include "froggers.hpp"

class Cell {
  Rectangle drawable;

 public:
  // Constructor
  Cell(Rectangle drawable);

  // Methods that draw and handle events

  void draw();
  void mouseClick(Point mouseLoc);
};
