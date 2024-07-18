#include "Board.hpp"

Board::Board(int size) : size(size) {

    // Initiate board tiles
    
    for (int x = 0; x < size; x++) {
        std::vector<Tile> tmp;

        for (int y = 0; y < size; y++) {
            tmp.push_back(Tile(Position{x, y}));
        }

        grid.push_back(tmp);
    }

}

bool Board::contains(Position pos) const {
    return pos.x < 13 && pos.y < 13 && pos.x >= 0 && pos.y >= 0;
}