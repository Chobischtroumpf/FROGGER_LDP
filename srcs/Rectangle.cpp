
#include "Rectangle.hpp"

Rectangle &Rectangle::operator=(const Rectangle &r) {
  center = r.center;
  w = r.w;
  h = r.h;
  fillColor = r.fillColor;
  frameColor = r.frameColor;
  return *this;
}

void Rectangle::draw() {
  std::array<Point, 5> points{Point{center.x - w / 2, center.y - h / 2},
                         Point{center.x - w / 2, center.y + h / 2},
                         Point{center.x + w / 2, center.y + h / 2},
                         Point{center.x + w / 2, center.y - h / 2},
                         Point{center.x - w / 2, center.y - h / 2}};

  fl_color(fillColor);
  fl_begin_polygon();
  for (auto &point : points) {
    fl_vertex(point.x, point.y);
  }
  fl_end_polygon();
  fl_color(frameColor);
  fl_begin_line();
  for (auto &point : points) {
    fl_vertex(point.x, point.y);
  }
  fl_end_line();
}

void Rectangle::setFillColor(Fl_Color newFillColor) {
  fillColor = newFillColor;
}

void Rectangle::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
}

bool Rectangle::contains(Point p) {
  return p.x >= center.x - w / 2 && p.x < center.x + w / 2 &&
         p.y >= center.y - h / 2 && p.y < center.y + h / 2;
}
