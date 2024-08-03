#ifndef DISPLAYSETTINGS_HPP
#define DISPLAYSETTINGS_HPP

#include "Coordinate.hpp"
// Forward declaration
class Coordinate;

// This class is used to store display settings
class DisplaySettings {
public:
	static int windowSize;
    static Coordinate boardCoords;
    static int boardViewSize;
	static int laneLength;
    static int tileSize;

};

#endif // DISPLAYSETTINGS_HPP