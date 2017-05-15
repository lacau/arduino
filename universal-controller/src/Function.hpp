//
//  Function.hpp
//  blink
//
//  Created by lacau on 14/05/2017.
//
//

#ifndef Function_hpp
#define Function_hpp

#include <Arduino.h>
#include <stdio.h>

class Function {

private:
    String name;
public:
    Function();
    Function(const String);
    ~Function();
    String getName();

protected:
};

#endif /* Function_hpp */
