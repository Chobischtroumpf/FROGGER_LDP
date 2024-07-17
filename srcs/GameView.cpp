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

void GameView::draw() {
    
    Fl_Window::draw();


    const std::vector<std::vector<Tile>>& grid = model->grid;
    
    // Draw the grid
    for (const auto& line : grid) {
        for (const auto& tile : line) {
           drawSquare(tile.pos, 50,FL_WHITE, FL_BLACK );
        }
    }

    drawSquare(model->frog.position, 40, FL_GREEN, FL_BLACK );
    
    frogBox->position(model->frog.position.x * 20, model->frog.position.y * 20);
    
}

void GameView::updateView() {
    redraw();
}