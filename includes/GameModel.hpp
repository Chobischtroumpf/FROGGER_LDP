#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <vector>
#include "Board.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

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

    std::vector<Level> levels;

    bool isGameOver;
    bool isVictory;
    int life = 3;
    int victoryScore = 0;
    int time = 0;
    int score = 0;

    Board board;
    Frog frog;
    std::vector<Vehicle> vehicles;


    GameModel();


    // Loads game levels from the levels/folder
    void loadLevels();

    // Updates each lane by moving their contained objects
    void updateLanes();   
    // Check if frog is on a moving platform, if so moves it
    void transportFrog(); 
    
    // Increases the score by the given value
    void increaseScore(int value);
    // Ends the game and saves the score
    void endGame();

    // Resets the finish lilipads
    void resetFinishLine();
    // Resets the timer
    void resetTimer();

    // Checks if the given position is safe for the frog
    bool isSafe(Position pos) const;
    bool tryEmptyLilyPad(Position pos);
private:
    
};

#endif // GAMEMODEL_HPP
