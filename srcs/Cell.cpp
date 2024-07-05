#include "Cell.hpp"

Cell::Cell(Point center, int w, int h, Canvas *canvas, Fl_Color frameColor, Fl_Color fillColor)
  : Rectangle{center, w, h, frameColor, fillColor}, canvas{canvas} {
  }

// getters

Moveable *Cell::getOccupant() {
  return occupant;
}

Canvas *Cell::getCanvas() {
  return canvas;
}

bool Cell::getIsSafe() {
  return isSafe;
}

// setters

void Cell::setCanvas(Canvas *canvas) {
  this->canvas = canvas;
}

void Cell::setOccupant(Moveable *occupant) {
  this->occupant = occupant;
}

// Methods that draw and handle events
void Cell::print() {
  Rectangle::print();
  if (occupant != nullptr) {
    occupant->print();
  }
}

Cell::~Cell() {
}