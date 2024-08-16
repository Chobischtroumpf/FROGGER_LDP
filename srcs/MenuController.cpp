#include "MenuController.hpp"

MenuController::MenuController(MenuModel* model, GameController* gameController)
    : model(model), gameController(gameController) {}

void MenuController::init() {
    setupMenus();
}

void MenuController::onKey(int key) {
	if (key == FL_Up) {
		shiftOption(-1);
	} else if (key == FL_Down) {
		shiftOption(1);
	} else if (key == FL_Enter) {
		handleMenuSelection(model->getSelectedOption());
	} else if (key == FL_Escape) {
        if (model->menuStack.top().title == "Main Menu") {
            return;
        }
        model->popMenu();
    // Reset the level's highscore when pressing X
    } else if (key == 'x') {
        // Check if we're in the level selection menu
        if (model->menuStack.top().title == "Levels") {
            gameController->resetHighScore(model->getSelectedLevel());
            // Blink the main menu so it updates the highscore
            model->popMenu();
            handleMenuSelection(0);
        }
    }
}

void MenuController::shiftOption(int inc) {
    int newOption = model->getSelectedOption() + inc;
    if (newOption < 0) {
        newOption = 0;
    } else if (newOption >= static_cast<int>(model->getOptions().size())) {
        newOption = static_cast<int>(model->getOptions().size()) - 1;
    }
    model->setSelectedOption(newOption);
}

void MenuController::startGame() {
    model->isMenu = false;
    gameController->startGame(model->selectedLevel);
    
    //Return to the main menu after the game is over
    model->popMenu();
}

void MenuController::handleMenuSelection(int selectedOption) {
    if (model->isMenuEmpty()) return;
    MenuModel::Menu& currentMenu = model->menuStack.top();
    currentMenu.handleSelection(selectedOption);
}


void MenuController::setupMenus() {
    // Main menu
    MenuModel::Menu mainMenu;
    mainMenu.title = "Main Menu";
    mainMenu.options = {"Play", "Exit"};
    mainMenu.handleSelection = [this](int selectedOption) {
        if (selectedOption == 0) {

            // Reload the levels
            gameController->reloadLevels();

            // Push the play menu
            MenuModel::Menu playMenu;
            playMenu.title = "Levels";
            playMenu.options = model->getLevelStrings();
            playMenu.options.push_back("Back");
            playMenu.handleSelection = [this, playMenu](int selectedOption) {
                            
                if (playMenu.options[selectedOption] == "Back") {
                    // Pop the options menu to go back
                    this->model->popMenu();
                    return;
                }
                
                

                // Print each level name for debugging
                for (const auto& level : this->model->levelList) {
                    std::cout << level.first << level.second.name << std::endl;
                }
                this->model->selectedLevel = this->model->getSelectedLevel();

                std::cout << "Selected level is : " << this->model->selectedLevel << std::endl;
                startGame();
            };
            this->model->pushMenu(playMenu);
        } else if (selectedOption == 1) {
            // Exit the game
            exit(0);;
        }
    };
    model->pushMenu(mainMenu);
}
