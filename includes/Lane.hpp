#ifndef LANE_HPP
#define LANE_HPP

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "Coordinate.hpp"
#include <cmath>
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

struct VehicleConfig {
    VehicleType type;
    int length;  // This can be used for any vehicle, but primarily for Logs.

    VehicleConfig(VehicleType type, int length = 1) : type(type), length(length) {}
};

enum LaneType {
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
    int length = 1;

    // Constructor
    Vehicle(Position pos, VehicleType t, Direction d ) 
        : position(pos), type(t), direction(d) {}
    
    Vehicle(Position pos, const VehicleConfig& config, Direction d) ;

    // Getter methods
    VehicleType getType() const;
    Direction getDirection() const;

    void move(int x); // Moves the vehicle x tiles along the lane direction
    bool collides(Position pos) const; // Checks if the vehicle collides with the given position
private:
    
    VehicleType type;
    Direction direction;
};

// Represents a simple pattern of vehicles to spawn
class SpawnPattern {
public:
    std::vector<VehicleConfig> pattern;
    // Delay between each vehicle spawn
    int delay;

    SpawnPattern(std::vector<VehicleConfig> p, int d) : pattern(p), delay(d), currentIndex(0), delayCounter(0) {}
    // Returns the next vehicle type in the pattern and updates the internal state
    VehicleConfig next();

    // Returns true if the next vehicle should be spawned
    bool tick();

private:
    int currentIndex;
    int delayCounter;
};

struct LaneConfig {
    LaneType type;
    Direction direction;
    int speed;
    SpawnPattern spawnPattern;
};

class Lane {
public:
    Lane(int length, int rowIndex, LaneType type, SpawnPattern pattern, Direction direction = Direction::Right);
    Lane(int length, int rowIndex, LaneConfig config);
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

    // Returns the tile at the given position
    Tile& hit(Position pos);
    // const version of the above method
    const Tile& hit(Position pos) const;
    
    int speed = 1;
private:
    int length;
    int rowIndex;
    
    LaneType type;
    Direction direction;
    SpawnPattern pattern;
    std::vector<Tile> tiles;
    std::vector<Vehicle> vehicles;
};

#endif // LANE_HPP
