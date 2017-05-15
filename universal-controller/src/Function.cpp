//
//  Function.cpp
//  blink
//
//  Created by lacau on 14/05/2017.
//
//

#include "Function.hpp"

Function::Function()  {
}

Function::Function(const String name)  {
    this->name = name;
}

String Function::getName()  {
    return name;
}

Function::~Function() {}
