#include "GameModel.hpp"
#include <iostream>

GameModel::GameModel() : isGameOver(false), board(13), frog({6,12}), frameCounter(0) {

}

void Frog2::move(int dx, int dy) {
    position.x += dx;
    position.y += dy;
}

void GameModel::update() {
    frameCounter++;

    if (frameCounter != 30){
        return;
    }

    frameCounter = 0;

     // Check if frog is on a moving platform, if so moves it
    Lane lane = board.getLanes()[frog.position.y]; 

    if( lane.getType() == LaneType::River){
        if (lane.getDirection() == Right){
            frog.move(+1, 0);
        } else {
            frog.move(-1,0);
        }
    }

    // Check if frog is out of bounds of board
    if (!board.contains(frog.position)){
        std::cout << "Out of bounds death" << std::endl;
        isGameOver = true;
        return;
    }

    // Updates each lane by moving their contained objects
    for (auto& lane : board.lanes) {
        lane.update(); // Update each lane
    }

    // Check for collisions, game over conditions, etc.
    // Check if frog collides with any vehicle
    if (!isSafe(frog.position)) {
        isGameOver = true;
        return;
    }

   
        
    
}

const bool GameModel::isSafe(Position pos) const{
    std::vector<Lane> lanes = board.getLanes();

    Lane lane = lanes.at(pos.y);

    return lane.isSafe(pos);
}

