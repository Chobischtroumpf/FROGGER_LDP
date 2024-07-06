#pragma once

#include <optional>
#include <iostream>
#include "Rectangle.hpp"
#include "Moveable.hpp"
#include "Point.hpp"

// Forward declaration of canvas, to avoid compile errors
class Canvas;

// The Frog class is a subclass of the Moveable and Rectangle classes,
// and it represents the frog that the player controls in the game.
class Frog: public virtual frogger::Moveable, public virtual Rectangle {
private:
  Point coordinates;
  Canvas *canvas = nullptr;
public:
  Frog(Point start_pos, Canvas *canvas);
  Frog &operator=(const Frog &other) = default;

  //getters
  // Cell* getCurrentCell() { return this->currentCell;};
  int getX() const;
  int getY() const;

  //setters
  // void setCurrentCell(Cell cell){ this->currentCell = &cell; }
  void setX(int x);
  void setY(int y);

  //methods
  // void draw() override;
  void keyPressed(int keyCode) override {(void)keyCode;};
  void moveLeft() override;
  void moveRight() override;
  void moveUp() override;
  void moveDown() override;

  //destructor
  ~Frog();
};