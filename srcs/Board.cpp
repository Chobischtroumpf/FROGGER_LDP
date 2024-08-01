#include "Board.hpp"

Board::Board(int size) : size(size) {

    // Initiate board Lanes ( and tiles )
    
    for (int i = 0; i < size; i++) {
        LaneType laneType = LaneType::Grass;
        Direction dir = Right;

        // Makes it easier to count lanes
        int y = 12 - i; 

        switch (y)
        {
        case 0 :
            laneType = LaneType::Grass;
            break;
        case 1 :
            laneType = LaneType::Road;
            dir = Left;
            break;
        case 2 :
            laneType = LaneType::Road;
            dir = Left;
            break;
        case 3 :
            laneType = LaneType::Road;
            dir = Left;
            break;
        case 4 :
            laneType = LaneType::Road;
            break;
        case 5 :
            laneType = LaneType::Road;
            break;
        case 7 :
            laneType = LaneType::River;
            break;
        case 8 :
            laneType = LaneType::River;
            break;
        case 9 :
            laneType = LaneType::River;
            break;
        case 10 :
            laneType = LaneType::River;
            break;
        case 11 :
            laneType = LaneType::River;
            break;
        default:
            break;
        }

        Lane lane = {size, i, laneType, dir};
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