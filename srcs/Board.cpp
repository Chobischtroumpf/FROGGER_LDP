#include "Board.hpp"

Board::Board(int size) : size(size) {

    // Initiate board Lanes ( and tiles )
    
    for (int i = 0; i < size; i++) {
        Lane lane = {size, i};

        lanes.push_back(lane);
    }

}

// Checks if given position if inside the board bounds
bool Board::contains(Position pos) const {
    return pos.x < 13 && pos.y < 13 && pos.x >= 0 && pos.y >= 0;
}

const std::vector<Lane>& Board::getLanes() const{
    return lanes;
}