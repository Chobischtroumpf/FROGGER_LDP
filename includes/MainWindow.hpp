#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <memory>
#include "Canvas.hpp"
#include "Notification.hpp"

class MainWindow : public Fl_Window {
  private:
    std::shared_ptr<Canvas> canvas;
    std::shared_ptr<Notification> notification = nullptr;
    int refreshPerSecond = 60;

\
 public:
  // Constructor
  MainWindow() :
    Fl_Window{500, 500, 650, 650, "Frogger Game"}, canvas{std::make_shared<Canvas>()} , refreshPerSecond{60} {
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);
    // notification = std::make_shared<Notification>(std::string("Hello World!"), Point{250, 250}, 20, FL_BLACK, 10);
  }

  // Methods that draw and handle events
  void draw() override {
    Fl_Window::draw();
    canvas->draw();
    if (notification != nullptr)
      notification->draw();
  }

  int handle(int event) override {
    switch (event) {
      case FL_PUSH:
        // canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_KEYDOWN:
        canvas->keyPressed(Fl::event_key());
        return 1;
      default:
        return 0;
    }
    return 0;
  }

  void reset() {
    Fl::remove_timeout(Timer_CB, this);
    Fl::add_timeout(1, Timer_Reset, this);
  }

  void resetCanvas() {
    if (canvas.unique() == true) 
      canvas.reset();
    canvas = std::make_shared<Canvas>();
    std::clog << "Resetting canvas" << std::endl;
    notification = nullptr;
    std::clog << "Deleting notification" << std::endl;
  }

  void resetLoop() {
    std::clog << "Removing timeout" << std::endl;
    Fl::remove_timeout(Timer_CB, this);
    std::clog << "Adding timeout" << std::endl;
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    std::clog << "Redrawing" << std::endl;
  }

  // timer loopback function
  static void Timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow *>(userdata);
    switch (o->canvas->getGameState()) {
      case GAMESTATE::WON:
        o->notification = std::make_shared<Notification>(std::string("You won!"), Point{325, 325}, 20, FL_BLACK, 10);
        o->reset();
        break;
      case GAMESTATE::GAMEOVER:
        o->notification = std::make_shared<Notification>(std::string("Game Over!"), Point{325, 325}, 20, FL_BLACK, 10);
        o->reset();
        break;
      case GAMESTATE::PLAYING:
      default:
        Fl::repeat_timeout(1.0 / o->refreshPerSecond, Timer_CB, userdata);
        break;
    }
    o->redraw();
  }

  static void Timer_Reset(void *userdata) {
    std::clog << "Timer_Reset" << std::endl;
    MainWindow *o = static_cast<MainWindow *>(userdata);
    o->resetCanvas();
    o->resetLoop();
  }

  // Destructor
  ~MainWindow() {
    Fl::remove_timeout(Timer_CB, this);
    Fl::remove_timeout(Timer_Reset, this);
  }
  
};
