//
//  Led.hpp
//  arduino
//
//  Created by lacau on 16/12/2016.
//
//

#ifndef Led_hpp
#define Led_hpp

#include <stdio.h>

class Led {

private:
  unsigned short pin;
  bool mode;

public:
    Led(const unsigned short, const bool);
    ~Led();
    unsigned short getPin() const;
    bool getMode() const;
    void switchMode();
protected:

};


#endif /* Led_hpp */
