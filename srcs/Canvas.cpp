#include "Canvas.hpp"
#include <iostream>

Canvas::Canvas(): frog{{6, 12}, this} {
  for (int x = 25; x < 650; x += 50) {
    std::vector<Cell> tmp;
    for (int y = 25; y < 650; y += 50) {
      tmp.push_back(Cell({x, y}, 50, 50, this));
    }
    this->grid.push_back(tmp);
  }
  this->grid[6][12].setOccupant(&frog);

  if (this->grid[6][12].getOccupant() == nullptr) {
    std::cout << "Frog not set" << std::endl;
  } else {
    std::cout << "Frog set" << std::endl;
  }
}

void Canvas::draw() {
  for (auto &line : this->grid) {
    for (auto &cell : line) {
      cell.print();
    }
  }
  frog.print();
}



void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case FL_Escape:
      exit(0);
      break;
    case FL_Left:
    case 'a':
    case 'q':
      this->moveLeft();
      break;
    case FL_Right:
    case 'd':
      this->moveRight();
      break;
    case FL_Up:
    case 'w':
    case 'z':
      this->moveUp();
      break;
    case FL_Down:
    case 's':
      this->moveDown();
      break;
    default:
      break;
      break;
    }  // pass (normal)
}

void Canvas::moveLeft() {
  if (this->frog.getX() > 0) {
    this->grid[this->frog.getY()][this->frog.getX()].setOccupant(nullptr);
    this->frog.moveLeft();
    this->grid[this->frog.getY()][this->frog.getX()].setOccupant(&this->frog);
  }
}

void Canvas::moveRight(){
  if (this->frog.getX() < 12) {
    this->grid[this->frog.getY()][this->frog.getX()].setOccupant(nullptr);
    this->frog.moveRight();
    this->grid[this->frog.getY()][this->frog.getX()].setOccupant(&this->frog);
  }
}

void Canvas::moveUp(){
  if (this->frog.getY() > 0) {
    this->grid[this->frog.getY()][this->frog.getX()].setOccupant(nullptr);
    this->frog.moveUp();
    this->grid[this->frog.getY()][this->frog.getX()].setOccupant(&this->frog);
  }
}

void Canvas::moveDown() {
  if (this->frog.getY() < 12) {
    this->grid[this->frog.getY()][this->frog.getX()].setOccupant(nullptr);
    this->frog.moveDown();
    this->grid[this->frog.getY()][this->frog.getX()].setOccupant(&this->frog);
  }
}

std::vector<Cell> &Canvas::operator[](std::size_t i) {
  return this->grid[i];
}

Canvas::~Canvas() {
  // nothing to do
}