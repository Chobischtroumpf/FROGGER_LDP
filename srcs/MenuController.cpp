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
}

void MenuController::handleMenuSelection(int selectedOption) {
    if (model->isMenuEmpty()) return;
    MenuModel::Menu& currentMenu = model->menuStack.top();
    currentMenu.handleSelection(selectedOption);
}


void MenuController::setupMenus() {
    // Main menu
    MenuModel::Menu mainMenu;
    mainMenu.options = {"Play", "Options", "Exit"};
    mainMenu.handleSelection = [this](int selectedOption) {
        if (selectedOption == 0) {
            
            // Reload the levels
            gameController->reloadLevels();

            // Push the play menu
            MenuModel::Menu playMenu;
            playMenu.options = model->levelList;
            playMenu.options.push_back("Back");
            playMenu.handleSelection = [this, playMenu](int selectedOption) {
                            
                if (playMenu.options[selectedOption] == "Back") {
                    // Pop the options menu to go back
                    this->model->popMenu();
                    return;
                }
                
                this->model->selectedLevel = playMenu.options[selectedOption];

                std::cout << "Selected level is : " << this->model->selectedLevel << std::endl;
                startGame();
            };
            this->model->pushMenu(playMenu);
        } else if (selectedOption == 1) {
            // Push the options menu
            MenuModel::Menu optionsMenu;
            optionsMenu.options = {"Sound", "Graphics", "Back"};
            optionsMenu.handleSelection = [this](int selectedOption) {
                if (selectedOption == 2) {
                    this->model->popMenu();
                }
                
            };
            this->model->pushMenu(optionsMenu);
        } else if (selectedOption == 2) {
            // Exit the game
            exit(0);
        }
    };
    model->pushMenu(mainMenu);
}
