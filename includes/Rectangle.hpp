#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include <array>
#include "Point.hpp"
# include "Drawable.hpp"

class Rectangle: public virtual frogger::Drawable {
  Point    center;
  int      w, h;
  Fl_Color fillColor, frameColor;

 public:
  Rectangle(Point center, int w, int h, Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE): 
            center{center}, w{w}, h{h},
            fillColor{fillColor},
            frameColor{frameColor} {};
  Rectangle(const Rectangle &r): center{r.center}, w{r.w}, h{r.h},
                                 fillColor{r.getFillColor()},
                                 frameColor{r.getFrameColor()} {};
  Rectangle &operator=(const Rectangle &r);

  // drawing method
  void      draw() override;
  bool      contains(Point p);
  
  // Getters
  Fl_Color  getFillColor() const { return fillColor; }
  Fl_Color  getFrameColor() const { return frameColor; }
  int       getWidth() const { return w; }
  int       getHeight() const { return h; }
  Point     getCenter() const { return center; }

  // Setters
  void      setFillColor(Fl_Color newFillColor);
  void      setFrameColor(Fl_Color newFrameColor);
  void      setWidth(int neww) { w = neww; }
  void      setHeight(int newh) { h = newh; }
  void      setCenter(Point p) { center = p;}
  
  // Destructor
  virtual ~Rectangle() {}
};
