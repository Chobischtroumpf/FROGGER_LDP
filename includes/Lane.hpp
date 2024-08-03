#ifndef LANE_HPP
#define LANE_HPP

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "Coordinate.hpp"

enum TileType {
    Classic,
    EmptyLilypad,
    CompletedLilypad
};

// Represents a tile of the game board
class Tile {
public:
    Position pos;
    TileType type = TileType::Classic;
    Tile(Position pos, TileType t) : pos(pos), type(t) {}

    void setTileType(TileType t) {
        type = t;
    }

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

    std::vector<Tile>& getTiles();
    const std::vector<Tile>& getTiles() const ;

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
