#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <vector>
#include "Board.hpp"


class Frog2 {
public:
    Position position;
    void move(int dx, int dy);
};

class GameModel {
public:
    bool isGameOver;
    Board board;
    Frog2 frog;
    std::vector<Vehicle> vehicles;

    
    

    

    GameModel();
    void update();
private:
    int frameCounter;
};

#endif // GAMEMODEL_HPP
