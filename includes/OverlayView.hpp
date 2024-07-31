#ifndef OVERLAYVIEW_HPP
#define OVERLAYVIEW_HPP

#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include <string>

class OverlayView : public Fl_Box {
public:
    OverlayView(int x, int y, int w, int h);

    void draw() override;
    void updateHUD(int life, bool isGameOver, bool isVictory);

private:
    bool gameOver;
    bool gameWon;
    std::string hudText;
};

#endif // OVERLAYVIEW_HPP
