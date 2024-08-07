#ifndef OVERLAYVIEW_HPP
#define OVERLAYVIEW_HPP

#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include <string>
#include "GameModel.hpp"

class OverlayView : public Fl_Box {
public:
    OverlayView(int x, int y, int w, int h, GameModel* model);

    void draw() override;
    void updateHUD();

private:
    GameModel* model;
    bool gameOver;
    bool gameWon;
};

#endif // OVERLAYVIEW_HPP
