#include "GameModel.hpp"
#include <iostream>


const Position Frog::startPosition = {(int)(round(6.5 * DisplaySettings::tileSize)), (int)(round(12.5 * DisplaySettings::tileSize))};

void Frog::resetPosition() {
    position = startPosition;
}

// Move the frog by dx and dy and update its rotation
void Frog::move(int dx, int dy, bool rotate ) {
    position.x += dx;
    position.y += dy;

    if(!rotate) {return;}

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

GameModel::GameModel() : isGameOver(false), isVictory(false), board(13), frog(Frog()) {

}

void GameModel::updateLanes() {
    for (auto& lane : board.lanes) {
        lane.update(); // Update each lane
    }
}

void GameModel::transportFrog() {
    
    // Check if frog is on a moving platform, if so moves it
    Lane lane = board.getLanes()[frog.position.tilePos().second]; 

    if( lane.getType() == LaneType::River){
        frog.move(lane.speed, 0, false);
    }
} 

void GameModel::resetFinishLine() {
    // Resets the finish lilipads
    Lane& lane = board.lanes[0];

    for (auto& tile : lane.getTiles()) {
        if (tile.type == TileType::CompletedLilypad){
            tile.setTileType(TileType::EmptyLilypad);
        }
    }
    
}


bool GameModel::isSafe(Position pos) const{
    std::vector<Lane> lanes = board.getLanes();

    Lane lane = lanes.at(pos.tilePos().second);

    return lane.isSafe(pos);
}

bool GameModel::tryEmptyLilyPad(Position pos)  {
    std::vector<Lane>& lanes = board.lanes;

    Lane& lane = lanes.at(pos.tilePos().second);

    Tile& tile = lane.hit(pos);
    bool isLilyPad = tile.type == TileType::EmptyLilypad;

    // If the tile is a lily pad, change it to a completed lily pad
    if (isLilyPad) {
        std::cout << "Setting tile to completed lily pad" << std::endl;
        tile.setTileType(TileType::CompletedLilypad);
    }
    return isLilyPad;
}


