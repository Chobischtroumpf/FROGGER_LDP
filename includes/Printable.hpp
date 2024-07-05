#pragma once

class Printable {
 public:
  virtual void print() = 0;
  virtual ~Printable() = default;
};
