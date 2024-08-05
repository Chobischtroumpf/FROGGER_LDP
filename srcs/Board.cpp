#include "Board.hpp"

Board::Board(int size) : size(size) {

    // Initiate board Lanes ( and tiles )
    
    for (int i = 0; i < size; i++) {
        LaneType laneType = LaneType::Grass;
        Direction dir = Right;
        SpawnPattern pattern = SpawnPattern({Car},0);

        // Makes it easier to count lanes
        int y = 12 - i; 

        switch (y)
        {
        case 0 :
            laneType = LaneType::Grass;
            break;
        case 1 :
            laneType = LaneType::Road;
            //dir = Left;
            pattern = SpawnPattern({Car}, 3);
            break;
        case 2 :
            laneType = LaneType::Road;
            dir = Left;
            pattern = SpawnPattern({Car, Bus}, 3);
            break;
        case 3 :
            laneType = LaneType::Road;
            dir = Left;
            pattern = SpawnPattern({Bus, Bus, Car}, 5);
            break;
        case 4 :
            laneType = LaneType::Road;
            pattern = SpawnPattern({Bus}, 5);
            break;
        case 5 :
            laneType = LaneType::Road;
            pattern = SpawnPattern({Car}, 5);
            break;
        case 7 :
            laneType = LaneType::River;
            pattern = SpawnPattern({{Log, 2}}, 3);
            break;
        case 8 :
            laneType = LaneType::River;
            pattern = SpawnPattern({{Log, 2}}, 3);
            break;
        case 9 :
            laneType = LaneType::River;
            pattern = SpawnPattern({Turtle}, 3);
            break;
        case 10 :
            laneType = LaneType::River;
            pattern = SpawnPattern({{Log, 5}}, 6);
            break;
        case 11 :
            laneType = LaneType::River;
            pattern = SpawnPattern({{Log, 3}, Turtle}, 4);
            break;
        case 12 :
            laneType = LaneType::FinishLine;
            break;
        default:
            break;
        }

        Lane lane = {size, i, laneType, pattern, dir};
        lanes.push_back(lane);
    }

}

// Checks if given position if inside the board bounds using the board size
bool Board::contains(Position pos) const {
    return !(pos.x < 0 || pos.x > DisplaySettings::boardViewSize || pos.y < 0 || pos.y > DisplaySettings::boardViewSize);
}

const std::vector<Lane>& Board::getLanes() const{
    return lanes;
}

Lane& Board::hit(Position pos) {
    int index = pos.tilePos().second;

    if (index < 0 || index >= static_cast<int>(lanes.size())) {
        throw std::runtime_error("Invalid index for lane");
    }

    return lanes.at(index);
}