#pragma once

#include <memory>
#include "Rectangle.hpp"
#include "Moveable.hpp"

using std::shared_ptr;
using frogger::Moveable;
class Canvas;

class Cell: public virtual Rectangle {
  private:
    Canvas  *canvas = nullptr;
    Moveable *occupant = nullptr;
    bool isSafe = true;

  public:
    // Constructor
    // The constructor of the Cell class receives a Point, two integers, and a Canvas reference
    Cell(Point center, int w, int h, Canvas *canvas, Fl_Color frameColor = FL_BLACK, Fl_Color fillColor = FL_WHITE);

    //getters
    Moveable *getOccupant();
    Canvas *getCanvas();
    bool getIsSafe();

    // drawing method
    void draw() override;

    //setters
    void setOccupant(Moveable *occupant);
    void setCanvas(Canvas *canvas);
    void setIsSafe(bool isSafe);

    // Destructor
    ~Cell();
};
