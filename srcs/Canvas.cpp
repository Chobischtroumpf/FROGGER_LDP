#include "Canvas.hpp"
#include <iostream>

Canvas::Canvas(): frog{{7, 12}, this}, frogInfo{"", Point{50, 25}, 20, FL_BLACK, 10}, gameState{GAMESTATE::PLAYING} {
  std::clog << "Canvas constructor" << std::endl;
  for (int x = 25; x < 750; x += 50) {
    std::vector<Cell> tmp;
    for (int y = 25; y < 650; y += 50) {
      tmp.push_back(Cell({x, y}, 50, 50, this));
    }
    this->grid.push_back(tmp);
  }
  this->grid[7][12].setOccupant(&frog);

  frogInfo.setString("Lives: " + std::to_string(frog.getLife()));

#ifdef OUTPUT_DEBUG
  if (this->grid[7][12].getOccupant() == nullptr) {
    std::clog << "Frog not set" << std::endl;
  } else {
    std::clog << "Frog set" << std::endl;
  }

  for (int i = 0; i < 13; i++) {
    this->grid[i][0].setIsSafe(false);
  }
#endif

}

void Canvas::resetFrogPosition() {
  this->grid[this->frog.getY()][this->frog.getX()].setOccupant(nullptr);
  this->frog.setX(7);
  this->frog.setY(12);
  this->grid[this->frog.getY()][this->frog.getX()].setOccupant(&this->frog);
}

void Canvas::updateGameState() {
  if (this->frog.getY() == 0) {
    this->gameState = GAMESTATE::WON;
  } else if (this->grid[this->frog.getY()][this->frog.getX()].getIsSafe() == false) {
    this->frog.loseLife();
    this->frogInfo.setString("Lives: " + std::to_string(frog.getLife()));
    this->resetFrogPosition();
    this->draw();
    if (this->frog.getLife() == 0) {
      this->gameState = GAMESTATE::GAMEOVER;
    }
  }
}

void Canvas::draw() {
  for (auto &line : this->grid) {
    for (auto &cell : line) {
      cell.draw();
    }
  }
  this->frogInfo.draw();
  this->frog.draw();
}



void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
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
  }
  this->updateGameState();
}

GAMESTATE Canvas::getGameState() const {
  return this->gameState;
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