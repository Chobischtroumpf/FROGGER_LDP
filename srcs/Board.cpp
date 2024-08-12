#include "Board.hpp"
#include <sstream>

std::istringstream getNextLine(std::istream& input) {
    std::string line;
    std::getline(input, line);
    return std::istringstream(line);
}

std::istream& operator>>(std::istream& is, LaneType& l) {
    int val;
    if (is >> val) {
        l = static_cast<LaneType>(val);
    }
    return is;
}

std::istream& operator>>(std::istream& is, Direction& d) {
    int val;
    if (is >> val) {
        d = static_cast<Direction>(val);
    }
    return is;
}

std::istream& operator>>(std::istream& is, VehicleType& v) {
    int val;
    if (is >> val) {
        v = static_cast<VehicleType>(val);
    }
    return is;
}

Level::Level(std::string encoded) {
    // Get the first line of the encoded string
    std::istringstream lvl(encoded);
    std::istringstream line;
    int score;

    getNextLine(lvl) >> score;

    for(int i = 0; i < 12; i++) {
        LaneType laneType;
        Direction dir;
        int speed;
        int delay;
        std::vector<VehicleConfig> pattern;

        getNextLine(lvl) >> laneType >> dir >> speed >> delay;
        
        VehicleType vType;
        int length;
        while(getNextLine(lvl) >> vType >> length) {
            pattern.push_back({vType, length});
        }

        this->lanes.push_back({laneType, dir, speed, SpawnPattern(pattern, delay) });
        
    }

    //Push the finish line
    this->lanes.push_back({FinishLine, Right, 0, SpawnPattern({}, 0) });

}

std::string Level::encode() const {
    std::ostringstream lvl;
    lvl << bestScore << std::endl;

    for (auto lane : lanes) {
        lvl << lane.type << " " << lane.direction << " " << lane.speed << " " << lane.spawnPattern.delay << std::endl;
        for (auto vehicle : lane.spawnPattern.pattern) {
            lvl << vehicle.type << " " << vehicle.length << std::endl;
        }
    }

    return lvl.str();
}

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