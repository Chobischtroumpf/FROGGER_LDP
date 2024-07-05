#include "Cell.hpp"

Cell::Cell(Point center, int w, int h, Canvas *canvas, Fl_Color frameColor, Fl_Color fillColor)
  : Rectangle{center, w, h, frameColor, fillColor}, canvas{canvas} {
  }

// Methods that set and get the occupant
void Cell::setOccupant(Moveable *occupant) {
  this->occupant = occupant;
}

Moveable *Cell::getOccupant() {
  return occupant;
}

// Methods that set and get the canvas

void Cell::setCanvas(Canvas *canvas) {
  this->canvas = canvas;
}

Canvas *Cell::getCanvas() {
  return canvas;
}

// Methods that draw and handle events
void Cell::print() {
  Rectangle::print();
  if (occupant != nullptr) {
    occupant->print();
  }
}

Cell::~Cell() {
  if (occupant != nullptr) {
    delete occupant;
  }
}