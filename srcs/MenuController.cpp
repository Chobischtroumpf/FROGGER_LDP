#include "MenuController.hpp"

MenuController::MenuController(MenuModel* model) : model(model) {}


void MenuController::onKey(int key) {
	if (key == FL_Up) {
		shiftOption(-1);
	} else if (key == FL_Down) {
		shiftOption(1);
	} else if (key == FL_Enter) {
		validateSelection();
	}
}

void MenuController::shiftOption(int inc) {
    int newOption = model->getSelectedOption() + inc;
    if (newOption < 0) {
        newOption = 0;
    } else if (newOption >= model->getOptions().size()) {
        newOption = model->getOptions().size() - 1;
    }
    model->setSelectedOption(newOption);
}

void MenuController::startGame() {
    model->isMenu = false;
}

void MenuController::validateSelection() {
    int selectedOption = model->getSelectedOption();
    if (selectedOption == 0) { // Start game
        startGame();
    } else if (selectedOption == 1) {
        // Show high scores
    } else if (selectedOption == 2) {
        // Quit game
        exit(0);
    }
}

