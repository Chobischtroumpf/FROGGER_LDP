#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Cell.hpp"
#include "Frog.hpp"

// The Canvas class is a class that represents the game board.
class Canvas {
  private:
    // The grid is a 2D vector of Cell objects
    std::vector<std::vector<Cell>> grid;
    // The frog is a shared pointer to a Frog object
    std::shared_ptr<Frog> frog;

  public:
    Canvas();
    void draw();
    void mouseClick(Point mouseLoc);
    void keyPressed(int keyCode);
};
