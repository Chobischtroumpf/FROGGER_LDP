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
#include "MenuView.hpp"

// Froward declaration to avoid circular dependency
class GameController;

class GameView : public Fl_Double_Window {
public:
    GameView(int w, int h, MenuModel* menuModel, GameModel* model, GameController* controller);

    int handle(int event) override;
    void draw() override;
    void updateView();

    // Start the game by showing the board and overlay
    void showGame();
    void hideGame();
private:
    GameModel* model;
    MenuModel* menuModel;
    GameController* controller;
    MenuView* mainMenu;
    OverlayView* overlayView;
    BoardView* boardView;
    Fl_Box* frogBox;
    std::vector<Fl_Box*> vehicleBoxes;
};

#endif // GAMEVIEW_HPP
