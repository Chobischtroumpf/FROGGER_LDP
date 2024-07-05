#pragma once

#include <optional>
#include "Rectangle.hpp"
#include "Moveable.hpp"
#include "Point.hpp"

// Forward declaration of canvas, to avoid compile errors
class Canvas;

// The Frog class is a subclass of the Moveable and Rectangle classes,
// and it represents the frog that the player controls in the game.
class Frog: public virtual Moveable, public virtual Rectangle {
  private:
    Point coordinates;
    Canvas *currentCell = nullptr;
  public:
    Frog(Point start_pos):  Rectangle{{start_pos.x*50+25, start_pos.y*50+25}, 30, 30, FL_RED, FL_BLUE},
                            coordinates{start_pos} {}
    Frog &operator=(const Frog &other) = default;
    
    //getters
    // Cell* getCurrentCell() { return this->currentCell;};
    int getX() const { return this->coordinates.x; }
    int getY() const { return this->coordinates.y; }

    //setters
    // void setCurrentCell(Cell cell){ this->currentCell = &cell; }
    void setX(int x) { this->coordinates.x = x; }
    void setY(int y) { this->coordinates.y = y; }
    
    //methods
    void print() override {Rectangle::print();};
    void keyPressed(int keyCode) override {
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
    };

    void moveLeft() override {
        if (this->getX() > 0) {
            this->setX(this->getX() - 1);
            // this->setCurrentCell(this->getCurrentCell()->getLeft());
            this->setCenter({this->getX()*50 + 25, this->getY()*50 + 25});
        }
    }
    void moveRight() override {
        if (this->getX() < 12) {
            this->setX(this->getX() + 1);
            // this->setCurrentCell(this->getCurrentCell()->getRight());
            this->setCenter({this->getX()*50 + 25, this->getY()*50 + 25});
        }
    }
    void moveUp() override {
        if (this->getY() > 0) {
            this->setY(this->getY() - 1);
            // this->setCurrentCell(this->getCurrentCell()->getUp());
            this->setCenter({this->getX()*50 + 25, this->getY()*50 + 25});
        }
    }
    void moveDown() override {
        if (this->getY() < 12) {
            this->setY(this->getY() + 1);
            // this->setCurrentCell(this->getCurrentCell()->getDown());
            this->setCenter({this->getX()*50 + 25, this->getY()*50 + 25});
        }
    }
    ~Frog() {currentCell = nullptr;}
};
