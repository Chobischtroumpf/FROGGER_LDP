#include "Frog.hpp"
#include "Canvas.hpp"

Frog::Frog(Point start_pos, Canvas *canvas):  Rectangle{{start_pos.x*50+25, start_pos.y*50+25}, 30, 30, FL_RED, FL_BLUE},
          coordinates{start_pos}, canvas{canvas} {
}

//getters
int Frog::getX() const {
  return this->coordinates.x;
}

int Frog::getY() const {
  return this->coordinates.y;
}

//setters
// void setCurrentCell(Cell cell){ this->currentCell = &cell; }
void Frog::setX(int x) {
  this->coordinates.x = x;
}

void Frog::setY(int y) {
  this->coordinates.y = y;
}

// //methods
// void Frog::draw() {
//   Rectangle::draw();
// }

void Frog::moveLeft() {
  if (this->getX() > 0) {
    this->setX(this->getX() - 1);
    this->setCenter({this->getX()*50 + 25, this->getY()*50 + 25});
  }
}

void Frog::moveRight() {
  if (this->getX() < 12) {
    this->setX(this->getX() + 1);
    this->setCenter({this->getX()*50 + 25, this->getY()*50 + 25});
  }
}

void Frog::moveUp()  {
  if (this->getY() > 0) {
    this->setY(this->getY() - 1);
    // this->setCurrentCell(this->getCurrentCell()->getUp());
    this->setCenter({this->getX()*50 + 25, this->getY()*50 + 25});
  }
}

void Frog::moveDown() {
  if (this->getY() < 12) {
    this->setY(this->getY() + 1);
    this->setCenter({this->getX()*50 + 25, this->getY()*50 + 25});
  }
}

Frog::~Frog() {
  canvas = nullptr;
}