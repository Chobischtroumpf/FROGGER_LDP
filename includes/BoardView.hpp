#ifndef BOARDVIEW_HPP
#define BOARDVIEW_HPP

#include <FL/Fl_Widget.H>
#include "GameModel.hpp"
#include "DrawingUtils.hpp"

class BoardView : public Fl_Widget {
public:
    BoardView(int x, int y, int w, int h, GameModel* model);
    void draw() override;

private:
    GameModel* model;
};

#endif // BOARDVIEW_HPP