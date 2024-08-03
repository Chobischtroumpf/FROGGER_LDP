// DisplaySettings.cpp
#include "DisplaySettings.hpp"

int DisplaySettings::windowSize = 1000;
int DisplaySettings::boardViewSize = 800;
Coordinate DisplaySettings::boardCoords = Coordinate((windowSize - boardViewSize) / 2, (windowSize - boardViewSize) / 2);
int DisplaySettings::laneLength = 13;
int DisplaySettings::tileSize = boardViewSize / laneLength;