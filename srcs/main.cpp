/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alessandro Dorigo                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:04:48 by adorigo           #+#    #+#             */
/*   Updated: 2023/11/13 16:04:49 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "froggers.hpp"

class MainWindow : public Fl_Window {
  Canvas canvas;
  static int refreshPerSecond;
 public:
  MainWindow(int windowWidth, int windowHeight, char *title, int refreshPerSecond) :
    Fl_Window(500, 500, windowWidth, windowHeight, title) {
    this->refreshPerSecond = refreshPerSecond;
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);
  }
  void draw() override {
    Fl_Window::draw();
    canvas.draw();
  }
  int handle(int event) override {
    switch (event) {
      case FL_PUSH:
        canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_KEYDOWN:
        canvas.keyPressed(Fl::event_key());
        return 1;
      default:
        return 0;
    }
    return 0;
  }
  static void Timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow *>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
  }
};

int main(int argc, char *argv[]) {
  MainWindow window(850, 850, "Frogger Game", 60);
  window.show(argc, argv);
  return Fl::run();
}
