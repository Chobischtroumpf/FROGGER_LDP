#include "GameModel.hpp"
#include <iostream>

GameModel::GameModel() : isGameOver(false), isVictory(false), board(13), frog({6,12}) {

}
Frog::Frog(Position pos) : position(pos) {
}

// Move the frog by dx and dy and update its rotation
void Frog::move(int dx, int dy) {
    position.x += dx;
    position.y += dy;

    // Update rotation so the frog faces the direction it's moving (counter-clockwise)
    if ( abs(dx) > abs(dy) ) {
        rotation = dx > 0 ? 270 : 90;
    } else {
        rotation = dy > 0 ? 180 : 0 ;
    }
}

int Frog::getRotation() const {
    return rotation;
}

void GameModel::updateLanes() {
    for (auto& lane : board.lanes) {
        lane.update(); // Update each lane
    }
}

void GameModel::transportFrog() {
    // Check if frog is on a moving platform, if so moves it
    Lane lane = board.getLanes()[frog.position.y]; 

    if( lane.getType() == LaneType::River){
        if (lane.getDirection() == Right){
            frog.move(+1, 0);
        } else {
            frog.move(-1,0);
        }
    }
}   

bool GameModel::isSafe(Position pos) const{
    std::vector<Lane> lanes = board.getLanes();

    Lane lane = lanes.at(pos.y);

    return lane.isSafe(pos);
}

bool GameModel::tryEmptyLilyPad(Position pos)  {
    std::vector<Lane>& lanes = board.lanes;

    Lane& lane = lanes.at(pos.y);

    Tile& tile = lane.getTiles().at(pos.x);
    bool isLilyPad = tile.type == TileType::EmptyLilypad;

    // If the tile is a lily pad, change it to a completed lily pad
    if (isLilyPad) {
        std::cout << "Setting tile to completed lily pad" << std::endl;
        tile.setTileType(TileType::CompletedLilypad);
    }
    return isLilyPad;
}


