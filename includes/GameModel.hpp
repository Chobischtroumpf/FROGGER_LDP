#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <vector>
#include "Board.hpp"
#include <iostream>

class Frog {
public:
    // The starting position of the frog, centered on a tile
    static const Position startPosition;
    Position position = startPosition;
    Frog(Position pos) : position(pos) {};
    Frog(){};

    void move(int dx, int dyn , bool rotate = true);
    void resetPosition();
    int getRotation() const;
private:
    int rotation = 0;
};

class GameModel {
public:
    bool isGameOver;
    bool isVictory;
    int life = 3;
    int victoryScore = 0;

    Board board;
    Frog frog;
    std::vector<Vehicle> vehicles;


    GameModel();
    // Updates each lane by moving their contained objects
    void updateLanes();   
    // Check if frog is on a moving platform, if so moves it
    void transportFrog(); 
    // Resets the finish lilipads
    void resetFinishLine(); 

    // Checks if the given position is safe for the frog
    bool isSafe(Position pos) const;
    bool tryEmptyLilyPad(Position pos);
private:
    
};

#endif // GAMEMODEL_HPP
