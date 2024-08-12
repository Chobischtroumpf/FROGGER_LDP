#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include "MenuModel.hpp"
#include <vector>
#include <string>
#include "DrawingUtils.hpp"

class MenuView : public Fl_Box {
public:
    MenuView(int x, int y, int w, int h, MenuModel* model);

private:
    void showSplashScreen();
    void shiftOption(int inc);

    void draw() override;

    
    int selectedOption = 0;
	MenuModel* model;
	bool isSplashScreen = true;
	
};

#endif // MENUVIEW_HPP