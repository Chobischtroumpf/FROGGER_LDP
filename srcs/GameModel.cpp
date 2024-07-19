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


    for (auto& lane : board.lanes) {
        lane.update(); // Update each lane
    }

    // Check for collisions, game over conditions, etc.
    // Check if frog collides with any vehicle
    for (const auto& lane : board.lanes) {
        for (const auto& vehicle : lane.getVehicles()) {
            if (vehicle.position == frog.position ) {
                isGameOver = true;
            }
        }
    }
}


