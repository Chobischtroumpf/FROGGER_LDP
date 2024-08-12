#include "MenuModel.hpp"

MenuModel::MenuModel() : selectedOption(0) {
    options = {"Play", "High Scores", "Exit"};
}

const std::vector<std::string>& MenuModel::getOptions() const {
    return options;
}

int MenuModel::getSelectedOption() const {
    return selectedOption;
}

void MenuModel::setSelectedOption(int option) {
    if (option >= 0 && option < options.size()) {
        selectedOption = option;
    }
}