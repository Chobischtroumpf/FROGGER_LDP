#pragma once

# include <FL/Fl.H>
# include <FL/Fl_Box.H>
# include <FL/Fl_Double_Window.H>
# include <FL/fl_draw.H>
# include <FL/Fl_Window.H>
#include "Canvas.hpp"

class MainWindow : public Fl_Window {
  private:
    Canvas canvas;
    int refreshPerSecond = 60;

 public:
  // Constructor
  MainWindow(int windowWidth, int windowHeight, std::string title, int refreshPerSecond) :
    Fl_Window(500, 500, windowWidth, windowHeight, title.c_str()), refreshPerSecond(refreshPerSecond) {
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);
  }

  // Methods that draw and handle events
  void draw() override {
    Fl_Window::draw();
    canvas.draw();
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
    o->redraw();
    Fl::repeat_timeout(1.0 / o->refreshPerSecond, Timer_CB, userdata);
  }
  
};
