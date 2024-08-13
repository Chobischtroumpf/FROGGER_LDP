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
    Level(std::vector<LaneConfig> lanes) : lanes(lanes) {};
    Level() {};

    std::string encode() const;
};

// Represents the game board.
class Board {
    public:
    Board(int size);


    Level level;
    
    // Load a level into the board
    void loadLevel(Level level);

    // the vector of lanes representing the board
    std::vector<Lane> lanes;
    const std::vector<Lane>& getLanes() const;

    Lane& hit(Position pos);
    // Checks if the given position is within the board.
    bool contains(Position pos) const;

    private:
    // We assume the board is square
    int size;
    
};


#endif // BOARD_HPP