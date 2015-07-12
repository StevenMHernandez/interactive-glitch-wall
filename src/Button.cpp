#include "Button.h"



#ifdef TARGET_RASPBERRY_PI
Button::Button() {
    if(wiringPiSetup() == -1){
        printf("Error on wiringPi setup");
    }
}
#else
Button::Button() {
    
}
#endif

#ifdef TARGET_RASPBERRY_PI
void Button::setPin(int _pin) {
    pin = _pin;
    pinMode(pin, INPUT);
    value = false;
}
#else
void Button::setPin(int _pin) {
    
}
#endif

#ifdef TARGET_RASPBERRY_PI
void Button::update() {
    isInitial = value ? false : true;
    value = digitalRead(pin) != 0 ? false : true;
}
#else
void Button::update() {
    
}
#endif

bool Button::isPressed() {
    return value;
}

bool Button::isInitialPress() {
    if(value) {
        return isInitial;
    } else {
        return false;
    }
}
