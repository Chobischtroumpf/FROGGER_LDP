#include "Canvas.hpp"

Canvas::Canvas(): frog({7, 0}) {
  for (int x = 25; x < 850; x += 50)
  {
    std::vector<Cell<Rectangle>> tmp;
    for (int y = 25; y < 850; y += 50)
    {
      tmp.push_back(Cell<Rectangle>(Rectangle({x, y}, 50, 50)));
    }
    cc.push_back(tmp);
  }
  this->frog.setCurrentCell(cc[frog.getY()][frog.getX()]);
}

void Canvas::draw() {
  for (auto &line : cc) {
    for (auto &cell : line) {
      cell.print();
    }
  }
}

// void Canvas::mouseClick(Point mouseLoc) {
//   for (auto &c : cc) c.mouseClick(mouseLoc);
// }

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
