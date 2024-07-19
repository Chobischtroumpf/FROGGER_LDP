#include "GameView.hpp"


GameView::GameView(int w, int h, GameModel* model, GameController* controller) 
    : Fl_Window(w, h), model(model), controller(controller)  {
    
    this->resizable(this); 

    frogBox = new Fl_Box(model->frog.position.x * 20, model->frog.position.y * 20, 20, 20, "Frog");

}

int GameView::handle(int event) {
    if (event == FL_KEYDOWN) {
        controller->handleKeyEvent(Fl::event_key());
        return 1; // Indicate that the event was handled
    }
    return Fl_Window::handle(event); // Let the base class handle other events
}

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

Fl_Color getVehicleColor(LaneType type){
    switch(type) {
        case LaneType::River:
            return FL_DARK_BLUE;
        case LaneType::Road:
            return FL_RED;
        default:
            return FL_WHITE;
    };
}

void GameView::draw() {
    
    Fl_Window::draw();


    const std::vector<Lane>& lanes = model->board.getLanes();
    
    // Draw the board
    for (const auto& lane : lanes) {
        Fl_Color fillColor =  getLaneColor(lane.getType());
        Fl_Color vColor =  getVehicleColor(lane.getType());

        // Draw Each tile
        for (const auto& tile : lane.getTiles()) {
           drawSquare(tile.pos, 50, fillColor, FL_BLACK );
        }

        // Draw each Vehicle
        for (const auto& v : lane.getVehicles()) {
           drawSquare(v.position, 40, vColor, FL_BLACK );
        }
    }

    // Draw the frog ( player)
    drawSquare(model->frog.position, 20, FL_GREEN, FL_BLACK );
    
    frogBox->position(model->frog.position.x * 20, model->frog.position.y * 20);
    
}

void GameView::updateView() {
    redraw();
}