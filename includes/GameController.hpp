#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include "GameModel.hpp"
#include "GameView.hpp"
#include <FL/Fl.H>
#include "MenuController.hpp"
#include "MenuModel.hpp"
#include <iostream>

// Forward declarations to avoid circular dependency
class GameView;
class MenuController;

class GameController {
public:
    GameController(MenuModel* menuModel, GameModel* model, GameView* view);

    void onKey(int key);
    void gameLoop();
    void handleKeyEvent(int key);

    void linkView(GameView* view){
        this->view = view;
    }

    void startGame(const std::string& level);
    // Reloads the levels from the files
    void reloadLevels();

private:
    GameModel* model;
    MenuModel* menuModel;
    MenuController* menuController;
    GameView* view;
    int frameCounter = 0;

   
    void update(); // Update the game state


    void resetPlayerPosition();
    void killPlayer();
    void resetGame();
    // Ends the game and clears the board
    void endGame();

    void movePlayer(int x, int y);
    void checkVictory();

};

#endif // GAMECONTROLLER_HPP