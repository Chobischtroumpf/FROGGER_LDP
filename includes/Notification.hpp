#pragma once


#include <iostream>
#include "Text.hpp"
#include "Rectangle.hpp"

class Notification : public virtual Text {
  private:
    Rectangle background;
    int       padding;

    // if we want to add a close button
    // Rectangle close;

  public:
    Notification(): Text(std::string(), {0,0},0), background{{0,0}, 0, 0}, padding{0} {}
    Notification(string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK, int padding = 10)
      : Text{s, center, fontSize, color}, background{center, getWidth() + padding * 2, getHeight() + padding * 2}, padding{padding} {
        // if we want to add a close button
        // close = Rectangle(Point(center.x + width / 2 + padding/2, center.y + height / 2 + padding/2), padding, padding, FL_BLACK, FL_RED);
        std::cout << "Notification created" << std::endl;
        std::cout << "Width: " << getWidth() << " Height: " << getHeight() << std::endl;
    }

    void draw() override {
      background.draw();
      Text::draw();
    }

    void setFontSize(int newFontSize) {
      Text::setFontSize(newFontSize);
      background.setHeight(getHeight() + padding * 2);
      background.setWidth(getWidth() + padding * 2);
    }

    void setCenter(Point newCenter) {
      Text::setCenter(newCenter);
      background.setCenter(newCenter);
    }

    void setString(const string &newString) {
      Text::setString(newString);
      background.setWidth(getWidth() + padding * 2);
      background.setHeight(getHeight() + padding * 2);
    }

    //Getters
    Rectangle getBackground() { return background; }
    int       getPadding() { return padding; }
};