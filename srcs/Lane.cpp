#include "Lane.hpp"


void Vehicle::move(int x) {
    // Move vehicle 
    position.x += x;
}

VehiclePart Vehicle::getPart() const {
    return part;
}
VehicleType Vehicle::getType() const {
    return type;
}

Direction Vehicle::getDirection() const {
    return direction;
}



Lane::Lane(int length, int rowIndex, LaneType type, Direction direction) : length(length), rowIndex(rowIndex), type(type), direction(direction), tiles(length, Tile({0, 0})) {
    // Initialize tiles with corresponding positions
    for (int i = 0; i < length; ++i) {
        tiles[i] = Tile({i, rowIndex}); 
    }
}

void Lane::spawnVehicle() {
    Position spawnPos;
    Position lastSpawnPos; // The position next to the spawn position

    if( direction == Right) {
        spawnPos = {0, rowIndex};
        lastSpawnPos = {1, rowIndex};
    } else {
        spawnPos = {length - 1, rowIndex};
        lastSpawnPos = {length - 2, rowIndex};
    }


    if (!getVehicles().empty()) {

        Vehicle lastVehicle = this->getVehicles().back();

        // Check if the spawn case of the lane already contained a vehicle
        if ( lastVehicle.position == lastSpawnPos ) {
            
            // Don't allow two vehicles to spawn adjacent.
            if( lastVehicle.getPart() == VehiclePart::End || lastVehicle.getPart() == VehiclePart::Single){ return; }
            
            // At this point we know we will spawn a vehicle part;
            VehicleType newType;
            VehiclePart newPart;

            switch(lastVehicle.getType()) {
                // Buses are two parts long, so we need to spawn the second part
                case Bus : 
                    newType = Bus;
                    newPart = End;
                    break;
                // Logs have no size limit, so we spawn a new log part randomly
                case Log:
                    newType = Log;
                    newPart = rand() % 2 == 0 ? Center : End;
                    break;
                default:
                    // Default case shouldn't happen, so throw an exception if reached
                    throw std::runtime_error("Invalid vehicle type");
            }
            
            vehicles.push_back(Vehicle{spawnPos, newType, newPart, getDirection()});

            return;
        }

    }
        
    // First determine if we spawn a vehicle
    if( rand() % 2 == 0) {
        return;
    }

    // If we do spawn a vehicle, determine the type
    VehicleType newType = generateVehicleType();
    VehiclePart newPart = newType == Bus || newType == Log ? Front : Single;

    vehicles.push_back(Vehicle{spawnPos, newType, newPart, getDirection()});

    
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
        spawnVehicle();
    }
    
}

const std::vector<Tile>& Lane::getTiles() const {
    return tiles;
}

const std::vector<Vehicle>& Lane::getVehicles() const {
    return vehicles;
}

LaneType Lane::getType() const {
    return type;
}
Direction Lane::getDirection() const {
    return direction;
}
bool Lane::isSafe(Position pos) const {
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