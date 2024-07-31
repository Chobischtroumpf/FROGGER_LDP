#include "OverlayView.hpp"
#include <FL/fl_draw.H>
#include <iostream>

OverlayView::OverlayView(int x, int y, int w, int h) : Fl_Box(x, y, w, h), gameOver(false), gameWon(false) {}

void OverlayView::updateHUD(int life, bool isGameover, bool isVictory) {

    // Build the life indicator string
    std::string heart = "❤️";
    std::string hearts;
    for (int i = 0; i < life; ++i) {
        hearts += heart;
    }


    hudText = hearts;

    this->gameOver = isGameover;
    this-> gameWon = isVictory;

    redraw();
}

void OverlayView::draw() {
    Fl_Box::draw();
    
    if (gameOver) {
        fl_color(FL_RED);
        fl_font(FL_HELVETICA_BOLD, 36);
        fl_draw("Game Over", x() + w() / 2 - 100, y() + h() / 2);
    } else if (gameWon) {
        fl_color(FL_GREEN);
        fl_font(FL_HELVETICA_BOLD, 36);
        fl_draw("You Win!", x() + w() / 2 - 100, y() + h() / 2);
    }
	
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA, 18);
    fl_draw(hudText.c_str(), x() + 10, y() + 30);
}
