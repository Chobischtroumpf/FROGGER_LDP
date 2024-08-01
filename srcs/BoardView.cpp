#include "BoardView.hpp"

BoardView::BoardView(int x, int y, int w, int h, GameModel* model)
    : Fl_Widget(x, y, w, h), model(model) {}


Fl_Color getLaneColor(LaneType type){
    switch(type) {
        case LaneType::Grass :
            return FL_DARK_GREEN;
        case LaneType::River:
            return FL_BLUE;
        case LaneType::Road:
            return FL_GRAY;
        default:
            return FL_WHITE;
    };
}

void BoardView::draw() {

    const std::vector<Lane>& lanes = model->board.getLanes();
    
    // Draw the board
    for (const auto& lane : lanes) {
        Fl_Color fillColor =  getLaneColor(lane.getType());

        // Draw Each tile
        for (const auto& tile : lane.getTiles()) {
           drawSquare(tile.pos, 50, fillColor, FL_BLACK );
        }

        // Draw each Vehicle
        for (const auto& v : lane.getVehicles()) {
           drawVehicle(v);
        }
    }

    // Draw the frog ( player)
    drawSquare(model->frog.position, 20, FL_GREEN, FL_BLACK );
}
