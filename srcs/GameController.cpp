#include "GameController.hpp"
#include <FL/Fl.H>

#include <iostream>

GameController::GameController(GameModel* model, GameView* view) 
    : model(model), view(view) {}

void GameController::onKey(int key) {
    switch (key) {
        case FL_Up:
            model->frog.move(0, -1);
            break;
        case FL_Down:
            model->frog.move(0, 1);
            break;
        case FL_Left:
            model->frog.move(-1, 0);
            break;
        case FL_Right:
            model->frog.move(1, 0);
            break;
    }
}

void GameController::handleKeyEvent(int key) {
    onKey(key);
}

/* The main loop of the game, it manages the game events */
void GameController::gameLoop() {
    //std::cout << "Gameloop trigger" << std::endl;

    if (!model->isGameOver) {
        model->update();
        view->updateView();
    }
}
