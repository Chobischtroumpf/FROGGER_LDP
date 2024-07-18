#ifndef DRAWINGUTILS_HPP
#define DRAWINGUTILS_HPP

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include "GameModel.hpp"

// Declare the functions
void drawFilledRect(int x, int y, int width, int height, Fl_Color fillColor, Fl_Color frameColor = FL_BLACK);
void drawSquare(Position pos, int size, Fl_Color fillColor = FL_WHITE, Fl_Color frameColor = FL_BLACK);

#endif // DRAWINGUTILS_HPP


