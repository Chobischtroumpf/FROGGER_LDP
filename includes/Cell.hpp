    #pragma once

    #include "Rectangle.hpp"
    #include "Canvas.hpp"

class Cell: public virtual Rectangle {
  private:
    Canvas  &canvas;
    Moveable *occupant = nullptr;

  public:
    // Constructor
    // The constructor of the Cell class receives a Point, two integers, and a Canvas reference
    Cell(Point center, int w, int h, Canvas &canvas, Fl_Color frameColor = FL_BLACK, Fl_Color fillColor = FL_WHITE)
        : Rectangle{center, w, h, frameColor, fillColor}, canvas{canvas} {}

    // Methods that draw and handle events
    void print();

    ~Cell() {}
};