#ifndef DRAWINGUTILS_HPP
#define DRAWINGUTILS_HPP

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include "GameModel.hpp"
#include "Point.hpp"

// Draw a filled rectangle with a frame
void drawFilledRect(int x, int y, int width, int height, Fl_Color fillColor, Fl_Color frameColor = FL_BLACK) {
    fl_color(fillColor);
    fl_rectf(x, y, width, height);

    fl_color(frameColor);
    fl_rect(x, y, width, height);
}

void drawSquare(Position pos, int size, Fl_Color fillColor = FL_WHITE, Fl_Color frameColor = FL_BLACK){
    
    int tileSize = 50;

    // Set the fill color and draw the filled square
    fl_color(fillColor);
    fl_rectf(pos.x * tileSize + ( tileSize - size ) / 2 , pos.y * tileSize + ( tileSize - size ) / 2, size, size);

    // Draw the border
    fl_color(frameColor);
    fl_rect(pos.x * tileSize + ( tileSize - size ) / 2, pos.y * tileSize + ( tileSize - size ) / 2, size, size);
}

#endif // DRAWINGUTILS_HPP
