#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <string>
#include <iostream>
#include "Point.hpp"
#include "Drawable.hpp"

using std::string;
using frogger::Drawable;

class Text: public Drawable {
  private:
    string   s;
    Point    center;
    int      fontSize;
    double   width;
    double   height;
    Fl_Color color;

    void setSize() {
      fl_font(FL_HELVETICA, fontSize);
      width = fl_width(s.c_str());
      height = fontSize;
      std::cout << "TEXT: Width: " << width << " Height: " << height << std::endl;
    }

  public:
    // Constructor
    Text(): s{""}, center{0,0}, fontSize{10}, color{FL_BLACK} {
      setSize();
    }

    Text(string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK)
        : s{s}, center{center}, fontSize{fontSize}, color{color} {
          setSize();
    }

    Text(const Text &t) : s{t.getString()}, center{t.getCenter()}, fontSize{t.getFontSize()}, color{t.getColor()} {
      setSize();
    }

    // Drawing method
    void draw() override;

    //Getters
    string getString() const { return s; }
    int    getFontSize() const { return fontSize; }
    Point  getCenter() const { return center; }
    Fl_Color getColor() const { return color; }
    int    getWidth() const { return width; }
    int    getHeight() const { return height; }

    // Setters

    void   setString(const string &newString) {
      s = newString;
      setSize();
    }

    void   setFontSize(int newFontSize) {
      fontSize = newFontSize;
      setSize();
    }
    
    void   setCenter(Point newCenter) { center = newCenter; }
    void   setColor(Fl_Color newColor) { color = newColor; }
};