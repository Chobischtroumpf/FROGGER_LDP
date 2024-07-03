#ifndef __FROGGERS_HPP
#define __FROGGERS_HPP

# include <FL/Fl.H>
# include <FL/Fl_Box.H>
# include <FL/Fl_Double_Window.H>
# include <FL/fl_draw.H>
# include <string>
# include <memory>


class Printable {
 public:
  virtual void print() = 0;
  virtual ~Printable() = default;
};


struct Point {
  int x, y;
};


class Moveable {
public:
    virtual void keyPressed(int keyCode) = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
    virtual ~Moveable() = default;
};

#endif //!__FROGGERS_HPP
