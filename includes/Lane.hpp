#ifndef LANE_HPP
#define LANE_HPP

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <iostream>

// Represents a position on the game board
struct Position {
    // x and y represent the coordinates on the game board,
    // where x is the horizontal (abscissa) and y is the vertical (ordinate) axis.
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

enum VehicleType { 
    
    Bus, // Road only. Is two parts long.
    Car, // Road only. Is one part long.
    Log, // River only. Has no size limit.
    Turtle // River only. Is one part long.

};

enum VehiclePart { 
    Front,
    Center,
    End,
    Single
};

enum class LaneType {
    Road,
    River,
    Grass,
    Railway,
    FinishLine
};

enum Direction {
    Right,
    Left
};

class Vehicle {
public:
    
    Position position;

    // Constructor
    Vehicle(Position pos, VehicleType t, VehiclePart p, Direction d ) 
        : position(pos), type(t), part(p), direction(d) {}

    // Getter methods
    VehicleType getType() const;
    VehiclePart getPart() const;
    Direction getDirection() const;

    void move(int x); // Moves the vehicle x tiles along the lane direction

private:
    
    VehicleType type;
    VehiclePart part;
    Direction direction;
};



class Lane {
public:
    Lane(int length, int rowIndex, LaneType type, Direction direction = Direction::Right);

    void spawnVehicle();
    VehicleType generateVehicleType();
    void update(); // Method to process each game tick

    // Returning a const reference to avoid copying and to prevent modification
    const std::vector<Tile>& getTiles() const;
    const std::vector<Vehicle>& getVehicles() const;
    LaneType getType() const;
    Direction getDirection() const;
    // Checks if the given position on the lane is safe
    bool isSafe(Position pos) const;
private:
    int length;
    int rowIndex;
    LaneType type;
    Direction direction;
    std::vector<Tile> tiles;
    std::vector<Vehicle> vehicles;
};

#endif // LANE_HPP
