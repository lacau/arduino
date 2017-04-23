//
//  Led.cpp
//  arduino
//
//  Created by lacau on 16/12/2016.
//
//

#include "Led.hpp"

Led::Led(const unsigned short pin, const bool mode)  {
  this->pin = pin;
  this->mode = mode;
}
Led::~Led() {}

unsigned short Led::getPin() const {
  return pin;
}

bool Led::getMode() const {
  return mode;
}

void Led::switchMode() {
  mode = !mode;
}
