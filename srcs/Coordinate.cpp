#include "Coordinate.hpp"


Coordinate::Coordinate(int x, int y) : x(x), y(y) {}

// This constructor is used to convert a Position to a Coordinate by taking into account the offset of the BoardView
// This corresponds to the top-left corner of the tile
Coordinate::Coordinate(Position pos) {
	x = DisplaySettings::boardCoords.x + pos.x * DisplaySettings::tileSize;
	y = DisplaySettings::boardCoords.y + pos.y * DisplaySettings::tileSize;
}