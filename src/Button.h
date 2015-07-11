#pragma once

#include "ofMain.h"
#include "wiringPi.h"

class Button{
    
public:
    void setPin(int);
    void update();
    bool isPressed();
    bool isInitialPress();
private:
    int pin;
    bool isInitial;
    bool value;
};
