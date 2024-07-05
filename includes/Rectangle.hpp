#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include <array>
#include "Point.hpp"
# include "Printable.hpp"

class Rectangle: public virtual Printable {
  Point    center;
  int      w, h;
  Fl_Color fillColor, frameColor;

 public:
  Rectangle(Point center, int w, int h, Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE): 
            center{center}, w{w}, h{h},
            fillColor{fillColor},
            frameColor{frameColor} {};
  void      print() override;
  void      setFillColor(Fl_Color newFillColor);
  Fl_Color  getFillColor() { return fillColor; }
  void      setFrameColor(Fl_Color newFrameColor);
  Fl_Color  getFrameColor() { return frameColor; }
  void      setWidth(int neww) { w = neww; }
  void      setHeight(int newh) { h = newh; }
  int       getWidth() { return w; }
  int       getHeight() { return h; }
  bool      contains(Point p);
  Point     getCenter() { return center; }
  void      setCenter(Point p) { center = p;}
  ~Rectangle() {}
};
