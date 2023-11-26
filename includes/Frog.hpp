#ifndef __FROG_HPP
#define __FROG_HPP

#include <optional>
#include "Froggers.hpp"
#include "Cell.hpp"

class Frog: public virtual Moveable, public virtual Rectangle {
  private:
    Point coordinates;
    Cell<Rectangle> *currentCell = nullptr;
  public:
    Frog(Point start_pos);
    Frog &operator=(const Frog &other) = default;
    
    //getters
    Cell<Rectangle>* getCurrentCell();
    int getX() const { return this->coordinates.x; }
    int getY() const { return this->coordinates.y; }
    
    //setters
    void setCurrentCell(Cell<Rectangle> cell);
    void setX(int x) { this->coordinates.x = x; }
    void setY(int y) { this->coordinates.y = y; }
    
    //methods
    void print() override;
    void keyPressed(int keyCode) override;
    

    ~Frog() {}
};

#endif //!__FROG_HPP