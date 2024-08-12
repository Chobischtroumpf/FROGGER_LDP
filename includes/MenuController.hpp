#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include "MenuModel.hpp"
#include <Fl/Fl.H>


class MenuController {
public:
    MenuController(MenuModel* model);

	void onKey(int key);
    void shiftOption(int inc);
    void validateSelection();

    void startGame();

private:
    MenuModel* model;
};

#endif // MENUCONTROLLER_HPP