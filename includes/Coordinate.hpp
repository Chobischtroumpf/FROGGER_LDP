
#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include "DisplaySettings.hpp"
#include <cmath>

// Represents a position on the game board
// Is no longer discrete, but continuous coordinates
struct Position {
    // x and y represent the coordinates on the game view,
    // where x is the horizontal (abscissa) and y is the vertical (ordinate) axis.
    int x, y;

    // Override the equality operator
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    // Return a pair of ints representing the position of a tile
    std::pair<int, int> tilePos() const;
};

// Represents absolute coordinates on the window
class Coordinate {
public:
	int x;
	int y;

	Coordinate(int x, int y);
	// This constructor is used to convert a Position to a Coordinate by taking into account the offset of the BoardView
	// This corresponds to the top-left corner of the tile
	Coordinate(Position);

};

#endif // COORDINATE_HPP