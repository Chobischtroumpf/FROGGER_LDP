#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include "MenuModel.hpp"
#include <Fl/Fl.H>
#include "GameController.hpp"
// Forward declaration of GameController
class GameController;

class MenuController {
public:
    MenuController(MenuModel* model, GameController* gameController);
    // Initialize by setting up the menus
    void init();

	void onKey(int key);
    void shiftOption(int inc);
    void handleMenuSelection(int selectedOption);
    void startGame();
    void setupMenus();
private:
    MenuModel* model;
    GameController* gameController;
};

#endif // MENUCONTROLLER_HPP