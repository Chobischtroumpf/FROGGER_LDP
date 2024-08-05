#include "Coordinate.hpp"


std::pair<int, int> Position::tilePos() const {
    return std::make_pair((int) round(x / DisplaySettings::tileSize), (int) round(y / DisplaySettings::tileSize));
}

Coordinate::Coordinate(int x, int y) : x(x), y(y) {}

// This constructor is used to convert a Position to a Coordinate by taking into account the offset of the BoardView
Coordinate::Coordinate(Position pos) {
	x = DisplaySettings::boardCoords.x + pos.x;
	y = DisplaySettings::boardCoords.y + pos.y;
}