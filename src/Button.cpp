#include "Button.h"

void Button::setPin(int _pin) {
    pin = _pin;
    pinMode(pin, INPUT);
    value = false;
}

void Button::update() {
    isInitial = value ? false : true;
    value = digitalRead(pin) != 0 ? false : true;
}

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
