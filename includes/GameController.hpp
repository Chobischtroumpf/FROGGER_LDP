#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include "GameModel.hpp"
#include "GameView.hpp"
#include <FL/Fl.H>
#include <iostream>

// Forward declaration to avoid circular dependency
class GameView;

class GameController {
public:
    GameController(GameModel* model, GameView* view);

    void onKey(int key);
    void gameLoop();
    void handleKeyEvent(int key);

    void linkView(GameView* view){
        this->view = view;
    }

private:
    GameModel* model;
    GameView* view;
    int frameCounter = 0;

    void update(); // Update the game state


    void resetPlayerPosition();
    void killPlayer();
    void resetGame();

    void movePlayer(int x, int y);
    void checkVictory();

};

#endif // GAMECONTROLLER_HPP