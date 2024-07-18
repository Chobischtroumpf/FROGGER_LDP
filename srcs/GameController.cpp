#include "GameController.hpp"


GameController::GameController(GameModel* model, GameView* view) 
    : model(model), view(view) {}

void GameController::onKey(int key) {
    switch (key) {
        case FL_Up:
            movePlayer(0, -1);
            break;
        case FL_Down:
            movePlayer(0, 1);
            break;
        case FL_Left:
            movePlayer(-1, 0);
            break;
        case FL_Right:
            movePlayer(1, 0);
            break;
    }
}

void GameController::handleKeyEvent(int key) {
    onKey(key);
}

void GameController::movePlayer(int x, int y){

    int boardSize = 13;

    Position pos = model->frog.position;

    Position newPos = Position{pos.x + x , pos.y + y};

    if (!model->board.contains(newPos)){
        std::cout << "Out of bounds" << std::endl;
        return;
    }

    model->frog.move(x, y);

}

// The main loop of the game, it manages the game events 
void GameController::gameLoop() {
    //std::cout << "Gameloop trigger" << std::endl;

    if (!model->isGameOver) {
        model->update();
        view->updateView();
    }
}
