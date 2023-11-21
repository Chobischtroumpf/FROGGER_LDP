#include "Canvas.hpp"

Canvas::Canvas() {
  for (int x = 25; x < 850; x += 50)
  {
    for (int y = 25; y < 850; y += 50)
    {
      cc.push_back(Cell<Rectangle>(Rectangle({x, y}, 50, 50)));
    }
  }
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
    case FL_Left:
      
    default: {
    }  // pass (normal)
  }
}
