#include "GameView.hpp"


GameView::GameView(int w, int h, GameModel* model, GameController* controller) 
    : Fl_Double_Window(w, h), model(model), controller(controller)  {

    this->resizable(this);
    this->color(FL_BLACK);

    // Get screen dimensions
    int screen_w = Fl::w();
    int screen_h = Fl::h();

    // Calculate center position
    int window_x = (screen_w - this->w()) / 2;
    int window_y = (screen_h - this->h()) / 2;
    // Center window
    this->position(window_x, window_y);

    // Initialize the BoardView
    boardView = new BoardView(0, 0, w, h, model);

    // Initialize the OverlayView
    overlay = new OverlayView(0, 0, w, h, model);

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
    overlay->updateHUD();
    redraw();
}