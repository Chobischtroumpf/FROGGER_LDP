#include "Canvas.hpp"

Canvas::Canvas(): frog{{6, 12}} {
    for (int x = 25; x < 650; x += 50)
    {
        std::vector<Cell<Rectangle>> tmp;
        for (int y = 25; y < 650; y += 50)
        {
        tmp.push_back(Cell<Rectangle>(Rectangle({x, y}, 50, 50)));
        }
        cc.push_back(tmp);
    }
  // this->frog.setCurrentCell(cc[frog.getY()][frog.getX()]);
}

void Canvas::draw() {
    for (auto &line : cc) {
        for (auto &cell : line) {
        cell.print();
        }
    }
    frog.print();
}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case FL_Escape:
      exit(0);
      break;
    default: {
      frog.keyPressed(keyCode);
      break;
    }  // pass (normal)
  }
}
