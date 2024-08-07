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

// General purpose drawing functions
void drawFilledRect(int x, int y, int width, int height, Fl_Color fillColor, Fl_Color frameColor = FL_BLACK);
void drawSquare(Position pos, int size, Fl_Color fillColor = FL_WHITE, Fl_Color frameColor = FL_BLACK);
void drawPNG(const char* filename, Position pos, int size);
// DGame related drawing functions
void drawVehicle(Vehicle v);
void drawPlayer(Position pos, int rotation);
void drawTile(Tile tile, Fl_Color fillColor = FL_WHITE);
void drawLilyPad(Position pos, int size);
// Overlay related drawing functions
void drawLife(int life);
void drawGameOver(bool winOrLose);
void drawScore(int score);
#endif // DRAWINGUTILS_HPP


