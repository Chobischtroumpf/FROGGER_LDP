#include "MenuView.hpp"
#include <chrono>

MenuView::MenuView(int x, int y, int w, int h, MenuModel* model) 
    : Fl_Box(x, y, w, h), model(model) {
    this->color(FL_BLACK);
    this->box(FL_FLAT_BOX); // No border

    this->showSplashScreen();
}

void MenuView::showSplashScreen() {
    // Set timer to toggle splash screen using FL timer
	Fl::add_timeout(3.0, [](void* v) {
		MenuView* menuView = (MenuView*)v;
		menuView->isSplashScreen = false;
	}, this);
}


void MenuView::draw() {
	Fl_Box::draw();
	if (isSplashScreen) {
		drawSplashScreen();
	} else {
		drawMenu(model->selectedOption);
	}
}
