#include "GameView.hpp"


GameView::GameView(int w, int h, MenuModel* menuModel, GameModel* model, GameController* controller) 
    : Fl_Double_Window(w, h), menuModel(menuModel), model(model), controller(controller)  {

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

    // Initialize the MenuView
    mainMenu = new MenuView(0, 0, w, h, menuModel);

    // Initialize the BoardView
    boardView = new BoardView(0, 0, w, h, model);

    // Initialize the OverlayView
    overlayView = new OverlayView(0, 0, w, h, model);

    

    // Initially hide game-specific views
    boardView->hide();
    overlayView->hide();

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

    if( menuModel->isMenu ){
        hideGame();
    } else {
        showGame();
    }

}

void GameView::updateView() {
    // Schedule the redrtaw of the overlay
    overlayView->updateHUD();
    redraw();
}

void GameView::showGame() {
    // Show the game-specific views
    boardView->show();
    overlayView->show();
    // Hide the main menu
    mainMenu->hide();
}

void GameView::hideGame() {
    // Hide the game-specific views
    boardView->hide();
    overlayView->hide();
    // Show the main menu
    mainMenu->show();
}