#include "DrawingUtils.hpp"

int tileSize = 50; // To be replaced with a dynamic value (no global variables)

Fl_Color getVehicleColor(VehicleType type){
    switch(type) {
        case VehicleType::Bus :
            return FL_YELLOW;
        case VehicleType::Car:
            return FL_RED;  
        case VehicleType::Log:
            return fl_rgb_color(55, 33, 0); // Brown
        case VehicleType::Turtle:
            return FL_DARK_GREEN;
        default:
            return FL_WHITE;
    };
}

// Draw a filled rectangle with a frame
void drawFilledRect(int x, int y, int width, int height, Fl_Color fillColor, Fl_Color frameColor ) {
    fl_color(fillColor);
    fl_rectf(x, y, width, height);

    fl_color(frameColor);
    fl_rect(x, y, width, height);
}

void drawSquare(Position pos, int size, Fl_Color fillColor , Fl_Color frameColor ){
    
    // Set the fill color and draw the filled square
    fl_color(fillColor);
    fl_rectf(pos.x * tileSize + ( tileSize - size ) / 2 , pos.y * tileSize + ( tileSize - size ) / 2, size, size);

    // Draw the border
    fl_color(frameColor);
    fl_rect(pos.x * tileSize + ( tileSize - size ) / 2, pos.y * tileSize + ( tileSize - size ) / 2, size, size);
}

// Draws a vehicle part on the board
void drawVehicle(Vehicle v) {
    int size = 30;

    Fl_Color vehicleColor = getVehicleColor(v.getType());
    fl_color(vehicleColor);

    switch(v.getPart()) {
        case VehiclePart::Front:
            // Draw the front part of the vehicle
            if (v.getDirection() == Direction::Right) {
                fl_rectf(v.position.x * tileSize, v.position.y * tileSize + ( tileSize - size ) / 2, ( tileSize + size ) / 2, size);
            } else {
                fl_rectf(v.position.x * tileSize + ( tileSize - size ) / 2, v.position.y * tileSize + ( tileSize - size ) / 2, (tileSize + size) / 2, size);

            }
            break;
        case VehiclePart::Center:
            // Set the fill color and draw the middle part of the vehicle
            fl_rectf(v.position.x * tileSize, v.position.y * tileSize + ( tileSize - size ) / 2, tileSize, size);
            break;
        case VehiclePart::End:
            if (v.getDirection() == Direction::Right) {
                fl_rectf(v.position.x * tileSize + ( tileSize - size ) / 2, v.position.y * tileSize + ( tileSize - size ) / 2, (tileSize + size) / 2, size);
            } else {
                fl_rectf(v.position.x * tileSize, v.position.y * tileSize + ( tileSize - size ) / 2, ( tileSize + size ) / 2, size);
            }
            break;
        case VehiclePart::Single:
            // Set the fill color and draw the single part of the vehicle
            fl_rectf(v.position.x * tileSize + ( tileSize - size ) / 2 , v.position.y * tileSize + ( tileSize - size ) / 2, size, size);
            break;
        default:
            break;
    }
}



