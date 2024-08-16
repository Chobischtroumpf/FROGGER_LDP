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
        levelStrings.push_back(level.first + (level.second.bestScore > 0 ? " - High Score : " + std::to_string(level.second.bestScore) : ""));
    }
    return levelStrings;
}

// Returns the name of the current selected level
std::string MenuModel::getSelectedLevel() const {
    
    if (menuStack.empty() || menuStack.top().title != "Levels") {
        return "";
    }

    Menu playMenu = menuStack.top();

    // Extract the level name without the high score part
    std::string selectedLevel = playMenu.options[selectedOption];
    auto pos = selectedLevel.find(" - High Score : ");
    if (pos != std::string::npos) {
        selectedLevel = selectedLevel.substr(0, pos);
    }

    return selectedLevel;
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