#ifndef DRAWINGUTILS_HPP
#define DRAWINGUTILS_HPP

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <cmath>
#include <iostream>
#include "GameModel.hpp"
#include "DisplaySettings.hpp"
#include "Coordinate.hpp"

// Declare the functions
void drawFilledRect(int x, int y, int width, int height, Fl_Color fillColor, Fl_Color frameColor = FL_BLACK);
void drawSquare(Position pos, int size, Fl_Color fillColor = FL_WHITE, Fl_Color frameColor = FL_BLACK);
void drawVehicle(Vehicle v);
void drawPlayer(Position pos, int rotation);
void drawPNG(const char* filename, Position pos, int size);
void drawTile(Tile tile, Fl_Color fillColor = FL_WHITE);
void drawLilyPad(Position pos, int size);
#endif // DRAWINGUTILS_HPP


