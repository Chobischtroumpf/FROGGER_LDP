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
        case FL_Enter:
            resetGame();
            break;
    }
}

void GameController::resetGame(){
    model->isGameOver = false;
    model->isVictory = false;
    model->victoryScore = 0;
    model->resetFinishLine();
    model->life = 3;
    model->frog.position =  Position{6,12};
}

// Resets the player position to the starting position
void GameController::resetPlayerPosition(){
    model->frog.position = Position{6,12};
}

// Kills the player and checks if the game is over
void GameController::killPlayer(){
    model->life--;
    
    if (model->life == 0){
        model->isGameOver = true;
    } else {
        resetPlayerPosition();
    }
}

void GameController::handleKeyEvent(int key) {
    onKey(key);
}

void GameController::movePlayer(int x, int y){

    if( model->isGameOver) {
        return;
    }
    
    Position pos = model->frog.position;

    Position newPos = Position{pos.x + x , pos.y + y};

    if (!model->board.contains(newPos)){
        std::cout << "Out of bounds" << std::endl;
        return;
    }

    model->frog.move(x, y);

    if (!model->isSafe(newPos)){
        killPlayer();
        return;
    }

    if(model->tryEmptyLilyPad(newPos)){
        model->victoryScore++;
        checkVictory();
        resetPlayerPosition();
    }
}

void GameController::checkVictory(){
    if (model->victoryScore == 5){
        model->isVictory = true;
    }
}

// Update the game state
void GameController::update() {
    // Siple frame counter to throttle the game loop
    frameCounter++;
    if (frameCounter != 30){
        return;
    }
    frameCounter = 0;

    // Mobile platform check
    model->transportFrog();

    // Check if frog is out of bounds of board
    if (!model->board.contains(model->frog.position)){
        std::cout << "Out of bounds death" << std::endl;
        killPlayer();
        return;
    }

    // Updates each lane by moving their contained objects
    for (auto& lane : model->board.lanes) {
        lane.update(); // Update each lane
    }

    // Check for collisions, game over conditions, etc.
    // Check if frog collides with any vehicle
    if (!model->isSafe(model->frog.position)) {
        killPlayer();
        return;
    }

}

// The main loop of the game, it manages the game events 
void GameController::gameLoop() {
    //std::cout << "Gameloop trigger" << std::endl;
        view->updateView();
    if (!model->isGameOver) {
        update();
        view->updateView();
    }
}
