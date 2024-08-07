#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <Fl/Fl_Double_Window.H>
#include "GameModel.hpp"
#include "GameController.hpp"
#include "DrawingUtils.hpp"
#include "OverlayView.hpp"
#include <iostream>
#include "BoardView.hpp"
// Froward declaration to avoid circular dependency
class GameController;

class GameView : public Fl_Double_Window {
public:
    GameView(int w, int h, GameModel* model, GameController* controller);

    int handle(int event) override;
    void draw() override;
    void updateView();

private:
    GameModel* model;
    GameController* controller;
    OverlayView* overlay;
    BoardView* boardView;
    Fl_Box* frogBox;
    std::vector<Fl_Box*> vehicleBoxes;
};

#endif // GAMEVIEW_HPP
