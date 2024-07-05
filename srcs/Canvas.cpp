#include "Canvas.hpp"

Canvas::Canvas(): frog{std::make_shared<Frog>(Point(6, 12))} {
  for (int x = 25; x < 650; x += 50) {
    std::vector<Cell> tmp;
    for (int y = 25; y < 650; y += 50) {
      tmp.push_back(Cell({x, y}, 50, 50, this));
    }
    this->grid.push_back(tmp);
  }
  // this->grid[6][12].setOccupant(frog);
}

void Canvas::draw() {
  for (auto &line : this->grid) {
    for (auto &cell : line) {
      cell.print();
    }
  }
  frog->print();
}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case FL_Escape:
      exit(0);
      break;
    default: {
      frog->keyPressed(keyCode);
      break;
    }  // pass (normal)
  }
}
