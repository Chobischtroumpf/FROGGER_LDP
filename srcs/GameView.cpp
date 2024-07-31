#include "GameView.hpp"


GameView::GameView(int w, int h, GameModel* model, GameController* controller) 
    : Fl_Window(w, h), model(model), controller(controller)  {

    this->resizable(this);

    // Initialize the BoardView
    boardView = new BoardView(0, 0, w, h, model);

    // Initialize the OverlayView
    overlay = new OverlayView(0, 0, w, h);

    end();
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

    
    

    
}

void GameView::updateView() {
    // Schedule the redrtaw of the overlay
    overlay->updateHUD(3, model->isGameOver, false);
    redraw();

   
}