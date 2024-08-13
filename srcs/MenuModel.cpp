#include "MenuModel.hpp"

MenuModel::MenuModel() : selectedOption(0) {
}

void MenuModel::setLevelList(const std::vector<std::string> levels) {
    levelList = levels;
}

const std::vector<std::string>& MenuModel::getOptions() const {
    return menuStack.top().options;
}

int MenuModel::getSelectedOption() const {
    return selectedOption;
}

void MenuModel::setSelectedOption(int option) {
    if (option >= 0 && option < getOptions().size()) {
        selectedOption = option;
    }
}

void MenuModel::pushMenu(const Menu& menu) {
    menuStack.push(menu);
    selectedOption = 0;
}

void MenuModel::popMenu() {
    if (!menuStack.empty()) {
        menuStack.pop();
        selectedOption = 0;
    }
}

bool MenuModel::isMenuEmpty() const {
    return menuStack.empty();
}