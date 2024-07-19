#ifndef LANE_HPP
#define LANE_HPP

#include <vector>

// Represents a position on the game board
struct Position {
    int x, y;

    // Override the equality operator
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

// Represents a tile of the game board
class Tile {
public:
    Position pos;

    Tile(Position p) : pos(p) {}
};

class Vehicle {
public:
    Position position;
    void move(int x);
};

enum class LaneType {
    Road,
    River,
    Grass,
    Railway
};

enum Direction {
    Right,
    Left
};

class Lane {
public:
    Lane(int length, int rowIndex, LaneType type, Direction direction = Direction::Right);

    void spawnVehicle();
    void update(); // Method to process each game tick

    // Returning a const reference to avoid copying and to prevent modification
    const std::vector<Tile>& getTiles() const;
    const std::vector<Vehicle>& getVehicles() const;

private:
    int length;
    int rowIndex;
    LaneType type;
    Direction direction;
    std::vector<Tile> tiles;
    std::vector<Vehicle> vehicles;
};

#endif // LANE_HPP
