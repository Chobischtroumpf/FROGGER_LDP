#include "Text.hpp"

void Text::setSize() {
  fl_font(FL_HELVETICA, fontSize);
  width = fl_width(s.c_str());
  height = fontSize;
  std::clog << "TEXT: Width: " << width << " Height: " << height << std::endl;
}


void Text::draw() {
  fl_color(color);
  fl_font(FL_HELVETICA, fontSize);
  fl_draw(s.c_str(), center.x - this->width / 2, center.y+this->height/3);
}
