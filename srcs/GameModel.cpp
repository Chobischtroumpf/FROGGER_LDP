#include "GameModel.hpp"
#include <iostream>

GameModel::GameModel() : isGameOver(false) {

    frog = Frog2({0,0});
    
    int size =  13;
    
    for (int x = 0; x < size; x++) {
        std::vector<Tile> tmp;

        for (int y = 0; y < size; y++) {
            tmp.push_back(Tile(Position{x, y}));
        }

        grid.push_back(tmp);
    }
    //this->grid[6][12].setOccupant(&frog);
}

void Frog2::move(int dx, int dy) {
    position.x += dx;
    position.y += dy;
}

void Vehicle::move() {
    // Move vehicle logic
    position.x += 1;
}

void GameModel::update() {
    for (auto& vehicle : vehicles) {
        vehicle.move();
    }
}


