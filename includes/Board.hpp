#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Lane.hpp"



// Represents the game board.
class Board {
    public:
    // the vector of lanes representing the board
    std::vector<Lane> lanes;

    // Checks if the given position is within the board.
    bool contains(Position pos) const;

    Board(int size);

    const std::vector<Lane>& getLanes() const;

    Lane& hit(Position pos);

    private:
    // We assume the board is square
    int size;
    
};


#endif // BOARD_HPP