//
//  Equipment.cpp
//  blink
//
//  Created by lacau on 14/05/2017.
//
//

#include "Equipment.hpp"

Equipment::Equipment()  {
}

Equipment::Equipment(const String name)  {
    this->name = name;
    this->selected = false;
}

String Equipment::getName()  {
    return name;
}

void Equipment::setSelected(const bool selected) {
  this->selected = selected;
}

bool Equipment::isSelected()  {
    return selected;
}

bool Equipment::addFunction(Function *f) {
  if(funcCount >= MAX_FUNC_SIZE)
    return false;

  functions[funcCount] = f;
  funcCount++;
  return true;
}

Equipment::~Equipment() {}
