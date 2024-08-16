#include "Board.hpp"
#include <sstream>
#include <algorithm>

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

Level::Level(std::string name, std::string encoded) {

    this->name = name;

    // Get the first line of the encoded string
    std::istringstream lvl(encoded);
    std::istringstream line;
    int score;

    getNextLine(lvl) >> score;

    this->bestScore = score;

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

        this->lanes.push_back({laneType, dir, speed, SpawnPattern(pattern, delay)});
    }

    // Insert the finish line at pos 0
    this->lanes.insert(this->lanes.begin(), {FinishLine, Right, 0, SpawnPattern({}, 0)});
}

std::string Level::encode() const {
    std::ostringstream lvl;
    lvl << bestScore << std::endl;

    for (auto lane : lanes) {
        if (lane.type == FinishLine) {
            continue;
        }
        lvl << lane.type << " " << lane.direction << " " << lane.speed << " " << lane.spawnPattern.delay << std::endl;
        for (auto vehicle : lane.spawnPattern.pattern) {
            lvl << vehicle.type << " " << vehicle.length << std::endl;
        }
        lvl << std::endl; // Empty line to separate lanes
    }

    return lvl.str();
}

Board::Board(int size) : size(size), level(Level()) {

    std::vector<LaneConfig> lanes = {
        {Grass, Right, 1, SpawnPattern({}, 0)},
        {Road, Left, 2, SpawnPattern({Car}, 3)},
        {Road, Left, 1, SpawnPattern({Car, Bus}, 3)},
        {Road, Left, 2, SpawnPattern({Bus, Bus, Car}, 5)},
        {Road, Right, 1, SpawnPattern({Bus}, 5)},
        {Road, Right, 1, SpawnPattern({Car}, 5)},
        {Grass, Right, 1, SpawnPattern({}, 0)},
        {River, Right, 1, SpawnPattern({{Log, 2}}, 3)},
        {River, Right, 1, SpawnPattern({{Log, 2}}, 3)},
        {River, Right, 1, SpawnPattern({Turtle}, 3)},
        {River, Right, 1, SpawnPattern({{Log, 5}}, 6)},
        {River, Right, 1, SpawnPattern({{Log, 3}, Turtle}, 4)},
        {FinishLine, Right, 0, SpawnPattern({}, 0)}
    };
    // Invert the lane order
    std::reverse(lanes.begin(), lanes.end());
    
    level = Level("Default", lanes);
}

void Board::loadLevel(Level level) {
    // Set the level and clear the lanes
    this->level = level;
    this->lanes.clear();

    // Load the level 
    for (int i = 0; i < size; i++) {
        this->lanes.push_back({size, i, level.lanes.at(i)});
    }
}

void Board::initLevel() {
    // Fast forward 600 ticks
    for (int i = 0; i < 600; i++) {
        for (auto& lane : lanes) {
            lane.update();
        }
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