//
//  Equipment.hpp
//  blink
//
//  Created by lacau on 14/05/2017.
//
//

#ifndef Equipment_hpp
#define Equipment_hpp

#include <Arduino.h>
#include <stdio.h>
#include "Function.hpp"

#define MAX_FUNC_SIZE 2

class Equipment {

private:
    String name;
    bool selected;
    Function *functions[MAX_FUNC_SIZE];
    unsigned short funcCount = 0;
public:
    Equipment();
    Equipment(const String);
    ~Equipment();
    String getName();
    void setSelected(const bool);
    bool isSelected();
    bool addFunction(Function *);

protected:
};


#endif /* Equipment_hpp */
