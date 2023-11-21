#ifndef RECTANGLE_HPP
# define RECTANGLE_HPP 1

# include "froggers.hpp" 
# include "Point.hpp" 
# include <array>
# include <chrono>
# include <iostream>
# include <string>
# include <vector>

class Rectangle {
  Point    center;
  int      w, h;
  Fl_Color fillColor, frameColor;

 public:
  Rectangle(Point center, int w, int h, Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE): 
            center{center}, w{w}, h{h},
            fillColor{fillColor},
            frameColor{frameColor} {};
  void     draw();
  void     setFillColor(Fl_Color newFillColor);
  Fl_Color getFillColor() { return fillColor; }
  void     setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor() { return frameColor; }
  void     setWidth(int neww) { w = neww; }
  void     setHeight(int newh) { h = newh; }
  int      getWidth() { return w; }
  int      getHeight() { return h; }
  bool     contains(Point p);
  Point    getCenter() { return center; }
};

#endif
