#pragma once

#include "ofMain.h"

#ifdef TARGET_RASPBERRY_PI
#include "wiringPi.h"
#endif

class Button{
    
public:
    Button();
    void setPin(int);
    void update();
    bool isPressed();
    bool isInitialPress();
private:
    int pin;
    bool isInitial;
    bool value;
};
