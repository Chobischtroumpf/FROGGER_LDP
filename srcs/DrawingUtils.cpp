#include "DrawingUtils.hpp"

// Draw a filled rectangle with a frame
void drawFilledRect(int x, int y, int width, int height, Fl_Color fillColor, Fl_Color frameColor ) {
    fl_color(fillColor);
    fl_rectf(x, y, width, height);

    fl_color(frameColor);
    fl_rect(x, y, width, height);
}

void drawSquare(Position pos, int size, Fl_Color fillColor , Fl_Color frameColor ){
    
    int tileSize = 50;

    // Set the fill color and draw the filled square
    fl_color(fillColor);
    fl_rectf(pos.x * tileSize + ( tileSize - size ) / 2 , pos.y * tileSize + ( tileSize - size ) / 2, size, size);

    // Draw the border
    fl_color(frameColor);
    fl_rect(pos.x * tileSize + ( tileSize - size ) / 2, pos.y * tileSize + ( tileSize - size ) / 2, size, size);
}