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
    Canvas canvas;
    std::shared_ptr<Notification> notification = nullptr;
    int refreshPerSecond = 60;

 public:
  // Constructor
  MainWindow(int windowWidth, int windowHeight, std::string title, int refreshPerSecond) :
    Fl_Window{500, 500, windowWidth, windowHeight, title.c_str()}, canvas{} , refreshPerSecond{refreshPerSecond} {
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);
    // notification = std::make_shared<Notification>(std::string("Hello World!"), Point{250, 250}, 20, FL_BLACK, 10);
  }

  // Methods that draw and handle events
  void draw() override {
    Fl_Window::draw();
    canvas.draw();
    if (notification != nullptr)
      notification->draw();
  }

  int handle(int event) override {
    switch (event) {
      case FL_PUSH:
        // canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_KEYDOWN:
        canvas.keyPressed(Fl::event_key());
        return 1;
      default:
        return 0;
    }
    return 0;
  }

  // timer loopback function
  static void Timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow *>(userdata);
    switch (o->canvas.getGameState()) {
      case GAMESTATE::WON:
        o->notification = std::make_shared<Notification>(std::string("You won!"), Point{250, 250}, 20, FL_BLACK, 10);
        break;
      case GAMESTATE::GAMEOVER:
        o->notification = std::make_shared<Notification>(std::string("Game Over!"), Point{250, 250}, 20, FL_BLACK, 10);
        break;
      default:
        break;
    }
    o->redraw();
    Fl::repeat_timeout(1.0 / o->refreshPerSecond, Timer_CB, userdata);
  }
  
};
