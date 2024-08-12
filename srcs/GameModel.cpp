#include "GameModel.hpp"



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

// Function to read a file and return its content as a string
std::string readFile(const std::string& path) {
    // Open the file 
    std::ifstream file(path, std::ios::binary);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        throw std::runtime_error("Coud not open file: " + path);
    }

    // Read the entire file
    std::ostringstream contentStream;
    contentStream << file.rdbuf();  

    // Close the file explicitly (optional, since destructor will close it anyway)
    file.close();

    // Convert buffer into a string and return it
    return contentStream.str();
} 
// ----------------- GameModel -----------------

GameModel::GameModel() : isGameOver(false), isVictory(false), board(13), frog(Frog()) {

}

void GameModel::loadLevels() {
    std::string path = "levels/";
    
    // Read all files in the levels folder
    std::filesystem::path levelsPath = std::filesystem::current_path() / "levels";
    for (const auto& entry : std::filesystem::directory_iterator(levelsPath)) {
        if (entry.is_regular_file()) {
            // Read the file and store the level
            Level level(readFile(entry.path().string()));
            levels.push_back(level);
        }
    }
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

void  GameModel::increaseScore(int value) {
    // Increases the score by the given value
    score += value;
}

void GameModel::endGame() {
    
    if(isVictory) {
        score += static_cast<int>(360000 / time); // Add time bonus to score
    }

    score += life * 150; // Add life bonus to score

    resetTimer();
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

void GameModel::resetTimer() {
    time = 0;
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


