#include "Canvas.hpp"

Canvas::Canvas() {
  for (int x = 50; x < 500; x += 100)
    cc.push_back({
        {{x, 400}, 50, 100}
    });
}

void Canvas::draw() {
  for (auto &c : cc) {
    c.draw();
  }
}

void Canvas::mouseClick(Point mouseLoc) {
  for (auto &c : cc) c.mouseClick(mouseLoc);
}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'q':
      exit(0);
      break;
    default: {
    }  // pass (normal)
  }
}
