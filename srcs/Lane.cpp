#include "Lane.hpp"


void Vehicle::move(int x) {
    // Move vehicle 
    position.x += x;
}

VehicleType Vehicle::getType() const {
    return type;
}

Direction Vehicle::getDirection() const {
    return direction;
}

// Check if the vehicle collides with the given position taking length and direction into account
bool Vehicle::collides(Position pos) const {
    if (direction == Direction::Right) {
        return pos.x <= position.x && pos.x > position.x - length * DisplaySettings::tileSize;
    } else {
        return pos.x >= position.x && pos.x < position.x + length * DisplaySettings::tileSize;
    }
}


VehicleConfig SpawnPattern::next() {
    // Return the next vehicle type in the pattern
    currentIndex = (currentIndex + 1) % pattern.size();

    return pattern[currentIndex];
}

bool SpawnPattern::tick() {
    // Return true if the next vehicle should be spawned
    delayCounter = (int)round( (delayCounter + 1) % (delay * 60));
    return delayCounter == 0;
}

Lane::Lane(int length, int rowIndex, LaneType type, SpawnPattern pattern, Direction direction) : length(length), rowIndex(rowIndex), type(type), direction(direction), pattern(pattern), tiles(length, Tile({0, 0}, Classic)) {
    // Initialize tiles with corresponding positions
    
    for (int i = 0; i < length; ++i) {
        // If the lane is a finish line, we need to add empty lilypads
        TileType tileType = ( type == LaneType::FinishLine && (i % 2 == 0 && i > 1 && i < length - 2)  ) ? TileType::EmptyLilypad: TileType::Classic;
        tiles[i] = Tile({i * DisplaySettings::tileSize, rowIndex * DisplaySettings::tileSize}, tileType); 
    }
}

// Constructor using LaneConfig
Lane::Lane(int length, int rowIndex, LaneConfig config) : length(length), rowIndex(rowIndex), type(config.type), direction(config.direction), pattern(config.spawnPattern), tiles(length, Tile({0, 0}, Classic)) {
        // Initialize tiles with corresponding positions
        
        for (int i = 0; i < length; ++i) {
            // If the lane is a finish line, we need to add empty lilypads
            TileType tileType = ( type == LaneType::FinishLine && (i % 2 == 0 && i > 1 && i < length - 2)  ) ? TileType::EmptyLilypad: TileType::Classic;
            tiles[i] = Tile({i * DisplaySettings::tileSize, rowIndex * DisplaySettings::tileSize}, tileType); 
        }

}

void Lane::spawnVehicle() {
    Position spawnPos;
    Position lastSpawnPos; // The position next to the spawn position

    if( direction == Right) {
        spawnPos = {0, rowIndex * DisplaySettings::tileSize};
        lastSpawnPos = {1, rowIndex * DisplaySettings::tileSize};
    } else {
        spawnPos = {length * DisplaySettings::tileSize - 1, rowIndex * DisplaySettings::tileSize};
        lastSpawnPos = {length * DisplaySettings::tileSize - 2, rowIndex * DisplaySettings::tileSize};
    }

    // // First determine if we spawn a vehicle
    // if( ! (rand() % 3 == 0) ) {
    //     return;
    // }

    if (pattern.tick() == false) {
        return;
    }

    // If we do spawn a vehicle, determine the type
    VehicleConfig newConfig = pattern.next();

    vehicles.push_back(Vehicle{spawnPos, newConfig, getDirection()});

}

// Generate a random vehicle type based on the lane type
VehicleType Lane::generateVehicleType() {
    switch (type){
        case LaneType::Road:
            return rand() % 2 == 0 ? Car : Bus;
        case LaneType::River: 
            return rand() % 2 == 0 ? Turtle : Log;
        default:
            throw std::runtime_error("Invalid lane type for vehicle generation");
    }
}

void Lane::update() {

    
    // Move existing vehicles
    for (auto v = vehicles.begin(); v != vehicles.end(); ) {
        if(direction == Direction::Right) {
            v->move(speed); // Move each vehicle
        } else {
            v->move(-speed); 
        }
        
        // If the vehicle reaches the end of the lane, remove it
        if (v->position.x >= length * DisplaySettings::tileSize || v->position.x < 0 ) {
            v = vehicles.erase(v); // Erase returns the next iterator
        } else {
            ++v; // Move to the next vehicle
        }
    }

    if ( type == LaneType::Road || type == LaneType::River ){
        spawnVehicle();
    }
    
}

const std::vector<Tile>& Lane::getTiles() const {
    return tiles;
}

std::vector<Tile>& Lane::getTiles() {
    return tiles;
}

const std::vector<Vehicle>& Lane::getVehicles() const {
    return vehicles;
}

LaneType Lane::getType() const {
    return this->type;
}
Direction Lane::getDirection() const {
    return direction;
}

bool Lane::isSafe(Position pos) const {

    switch( type) {

        // Checks if there is a vehicle at the given pos, pos is safe otherwise
        case LaneType::Road:
            for( auto& v : vehicles){
                if (v.collides(pos)) {
                    return false;
                }
            }
            return true;

        // Checks if there is a vehicle at the given pos, pos is not safe otherwise
        case LaneType::River:
            for( auto& v : vehicles){
                if( v.collides(pos)  ){
                    return true;
                }
            }
            return false;
            
        case LaneType::FinishLine:
            std::cout << "Checking finish line" << hit(pos).type << std::endl;
            return this->hit(pos).type == TileType::EmptyLilypad;
        default:
            return true;
    }
}

Tile& Lane::hit(Position pos) {
    // Returns the tile at the given position
    int index = round(pos.x / DisplaySettings::tileSize);

    if (index < 0 || index >= static_cast<int>(tiles.size())) {
        throw std::runtime_error("Invalid index for lane tile");
    };

    return tiles.at( index );
}

const Tile& Lane::hit(Position pos) const {
    // Returns the tile at the given position
    int index = round(pos.x / DisplaySettings::tileSize);
    
    if (index < 0 || index >= static_cast<int>(tiles.size())) {
        throw std::runtime_error("Invalid index for lane tile");
    };

    return tiles.at( index );
}