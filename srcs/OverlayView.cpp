#include "OverlayView.hpp"
#include "DrawingUtils.hpp"
#include <iostream>

OverlayView::OverlayView(int x, int y, int w, int h, GameModel* model) : Fl_Box(x, y, w, h), model(model), gameOver(false), gameWon(false) {}

void OverlayView::updateHUD() {
    redraw();
}

void OverlayView::draw() {
    Fl_Box::draw();
    
    drawLife(model->life);
	
    drawScore(model->score);
}
