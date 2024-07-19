#include "Lane.hpp"

void Vehicle::move(int x) {
    // Move vehicle 
    position.x += x;
}

Lane::Lane(int length, int rowIndex, LaneType type, Direction direction) : length(length), rowIndex(rowIndex), type(type), direction(direction), tiles(length, Tile({0, 0})) {
    // Initialize tiles with corresponding positions
    for (int i = 0; i < length; ++i) {
        tiles[i] = Tile({i, rowIndex}); 
    }
}

void Lane::spawnVehicle() {
    Position spawnPos;

    if( direction == Right) {
        spawnPos = {0, rowIndex};
    } else {
        spawnPos = {length - 1, rowIndex};
    }
    
    vehicles.push_back(Vehicle{spawnPos});
}

void Lane::update() {

    
    // Move existing vehicles
    for (auto v = vehicles.begin(); v != vehicles.end(); ) {
        if(direction == Direction::Right) {
            v->move(+1); // Move each vehicle
        } else {
            v->move(-1); 
        }
        
        // If the vehicle reaches the end of the lane, remove it
        if (v->position.x >= length || v->position.x < 0 ) {
            v = vehicles.erase(v); // Erase returns the next iterator
        } else {
            ++v; // Move to the next vehicle
        }
    }

    if ( type == LaneType::Road || type == LaneType::River ){
        // Spawn new vehicle randomly
        if (std::rand() % 10 < 3) {

            spawnVehicle();
        }
    }
    
}

const std::vector<Tile>& Lane::getTiles() const {
    return tiles;
}

const std::vector<Vehicle>& Lane::getVehicles() const {
    return vehicles;
}

const LaneType Lane::getType() const {
    return type;
}
const Direction Lane::getDirection() const {
    return direction;
}
const bool Lane::isSafe(Position pos) const {
    switch( type) {

        // Checks if there is a vehicle at the given pos, pos is safe otherwise
        case LaneType::Road:
            for( auto& v : vehicles){
                if( v.position == pos ){
                    return false;
                }
            }
            return true;

        // Checks if there is a vehicle at the given pos, pos is not safe otherwise
        case LaneType::River:
            for( auto& v : vehicles){
                if( v.position == pos ){
                    return true;
                }
            }
            return false;
        default:
            return true;
    }
}