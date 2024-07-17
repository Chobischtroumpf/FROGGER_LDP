#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "GameModel.hpp"
#include "GameController.hpp"
#include "DrawingUtils.hpp"
#include <iostream>

// Froward declaration to avoid circular dependency
class GameController;

class GameView : public Fl_Window {
public:
    GameView(int w, int h, GameModel* model, GameController* controller);

    int handle(int event) override;
    void draw() override;
    void updateView();

private:
    GameModel* model;
    GameController* controller;
    Fl_Box* frogBox;
    std::vector<Fl_Box*> vehicleBoxes;
};

#endif // GAMEVIEW_HPP
