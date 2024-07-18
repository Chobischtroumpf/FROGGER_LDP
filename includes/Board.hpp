#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

// Represents a position on the game board
struct Position {
    int x, y;
};

// Represents a tile of the game board
class Tile {
public:
    Position pos;

    Tile(Position p) : pos(p) {}
};

// Represents the game board.
class Board {
    public:
    // The grid is a 2D vector of Cell objects
    std::vector<std::vector<Tile>> grid;

    // Checks if the given position is within the board.
    bool contains(Position pos) const;

    Board(int size);

    private:
    // We assume the board is square
    int size;
    
};


#endif // BOARD_HPP