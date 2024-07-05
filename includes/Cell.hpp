#pragma once

#include "Rectangle.hpp"
#include "Moveable.hpp"

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

    //setters
    void setOccupant(Moveable *occupant);
    void setCanvas(Canvas *canvas);


    // Methods that draw and handle events
    void print();

    // Destructor
    ~Cell();
};
