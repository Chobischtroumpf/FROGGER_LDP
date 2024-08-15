#include "MenuModel.hpp"

MenuModel::MenuModel() : selectedOption(0) {
}

void MenuModel::setLevelList(std::map<std::string, Level> levels) {
    levelList = levels;
}

std::vector<std::string> MenuModel::getLevelStrings() {
    std::vector<std::string> levelStrings;
    for (const auto& level : levelList) {
        // Add the level name to the vecotr + the highscore if its not null
        // print the level name and highscore for debugging
        std::cout << level.first << level.second.bestScore << std::endl;

        levelStrings.push_back(level.first + (level.second.bestScore > 0 ? " - High Score : " + std::to_string(level.second.bestScore) : ""));
    }
    return levelStrings;
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