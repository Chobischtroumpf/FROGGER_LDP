#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Drawable.hpp"
#include "Cell.hpp"
#include "Frog.hpp"

typedef enum {RESET, PLAYING, WON, GAMEOVER} GAMESTATE;

// The Canvas class is a class that represents the game board.
class Canvas: public virtual frogger::Drawable{
  private:
    // The grid is a 2D vector of Cell objects
    std::vector<std::vector<Cell>> grid;

    // The frog is a shared pointer to a Frog object
    Frog frog;

    // The gameState is an enum that represents the current state of the game
    GAMESTATE gameState;

    void updateGameState();

  public:
    Canvas();
    
    // handlers
    void draw() override;
    void keyPressed(int keyCode);

    // access operator
    std::vector<Cell> &operator[](std::size_t i); 

    // getters
    GAMESTATE getGameState() const;

    // movement methods
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // destructor
    ~Canvas();
};
