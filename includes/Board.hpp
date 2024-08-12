#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Lane.hpp"
#include <tuple>




// Represent a level confirugation
struct Level {
    // A vector of tuple of lanetype, speed and spawn pattern
    std::vector<LaneConfig> lanes;

    int bestScore = 0;
    
    // Decode a level from a string
    Level(std::string encoded);

    std::string encode() const;
};

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