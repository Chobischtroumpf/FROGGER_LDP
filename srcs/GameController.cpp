#include "GameController.hpp"


GameController::GameController(MenuModel* menuModel, GameModel* model, GameView* view) 
    :  model(model), menuModel(menuModel), view(view) {
        // Pass itself to the controller
        menuController = new MenuController(menuModel, this);

        // Load the levels from the files
        menuModel->setLevelList(model->loadLevels());
        
        // Initialize the menu
        menuController->init();

}

// The main loop of the game, it manages the game events 
void GameController::gameLoop() {
    //std::cout << "Gameloop trigger" << std::endl;

    view->updateView();

    if(menuModel->isMenu){
        return;
    }

    if (!model->isGameOver) {
        update();
        view->updateView();
    }
}

void GameController::onKey(int key) {
    
    if(menuModel->isMenu){
        std::cout << "Menu key event" << std::endl;
        menuController->onKey(key);
        return;
    }

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
        case FL_Escape:
            exitGame();
            
            break;
    }
}

void GameController::handleKeyEvent(int key) {
    onKey(key);
}

void GameController::startGame(const std::string& level) {
    // Load the selected level into the board
    model->startLevel(level);
    view->showGame();
}

void GameController::reloadLevels(){
    menuModel->setLevelList(model->loadLevels());
}

void GameController::resetGame(){
    model->isGameOver = false;
    model->isVictory = false;
    model->victoryScore = 0;
    model->resetFinishLine();
    model->life = 3;
    model->resetTimer();
    model->score = 0;
    resetPlayerPosition();
}

// Resets the player position to the starting position
void GameController::resetPlayerPosition(){
    model->frog.resetPosition();
}

// Kills the player and checks if the game is over
void GameController::killPlayer(){
    model->life--;
    
    if (model->life == 0){
        model->endGame();
        model->isGameOver = true;
    } else {
        resetPlayerPosition();
    }
}


void GameController::movePlayer(int x, int y){

    if( model->isGameOver) {
        return;
    }
    
    Position pos = model->frog.position;

    Position newPos = Position{pos.x + x * DisplaySettings::tileSize , pos.y + y * DisplaySettings::tileSize};

    if (!model->board.contains(newPos)){
        std::cout << "Out of bounds" << std::endl;
        return;
    }

    model->frog.move(x * DisplaySettings::tileSize, y * DisplaySettings::tileSize);

    if (!model->isSafe(newPos)){
        killPlayer();
        return;
    }

    // Increase score for each case forward the frog moves
    if( y != 0){
        model->increaseScore(y > 0 ? -10 : 10);
    }

    // Check if frog reached a lily pad
    if(model->tryEmptyLilyPad(newPos)){
        model->victoryScore++;
        model->increaseScore(100); // Increase score for reaching a lily pad
        checkVictory();
        resetPlayerPosition();
    }
}

void GameController::checkVictory(){
    if (model->victoryScore == 5){
        model->isVictory = true;
        model->endGame();
    }
}

// Update the game state
void GameController::update() {
    // Increment the time
    model->time++;

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



void GameController::exitGame(){
    resetGame();
    menuModel->isMenu = true;
}
