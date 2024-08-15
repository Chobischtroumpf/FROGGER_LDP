#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include <vector>
#include <string>
#include <functional>
#include <stack>
#include <iostream>
#include <map>
#include "Board.hpp"


class MenuModel {
public:
	// Structure for menu options and submenus
	struct Menu {
		std::vector<std::string> options;
		std::function<void(int)> handleSelection;
	};

    MenuModel();
    
	const std::vector<std::string>& getOptions() const;
    
	int getSelectedOption() const;
	void setSelectedOption(int option);
	
	bool isMenu = true;
	int selectedOption;
	std::string selectedLevel = "Level 1";

	// List of levels
	std::map<std::string, Level> levelList;

	void setLevelList(std::map<std::string, Level> levels);
	// Returns a vector of level name and highscore strings
	std::vector<std::string> getLevelStrings();
	

	void pushMenu(const Menu& menu);
    void popMenu();
    bool isMenuEmpty() const;
	void setupMenus(MenuModel* model);

	// Stack to manage the current menu state
	std::stack<Menu> menuStack;
private:    
};

#endif // MENUMODEL_HPP