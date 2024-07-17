#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <vector>
#include "Point.hpp"

struct Position {
    int x, y;
};

class Tile {
public:
    Position pos;

    Tile(Position p) : pos(p) {}
};

class Frog2 {
public:
    Position position;
    void move(int dx, int dy);
};

class Vehicle {
public:
    Position position;
    void move();
};

class GameModel {
public:
    Frog2 frog;
    std::vector<Vehicle> vehicles;
    
    // The grid is a 2D vector of Cell objects
    std::vector<std::vector<Tile>> grid;

    bool isGameOver;

    GameModel();
    void update();
};

#endif // GAMEMODEL_HPP
