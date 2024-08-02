#include "Button.h"
#include "Arduino.h"

Button::Button(int pin) {
    this->pin = pin;
    this->state = false;
}

bool Button::pressed(void) {
    if (digitalRead(pin) == LOW && state == false) {
        state = true;
        return true;
    }
    return false;
}

bool Button::released(void) {
    if (digitalRead(pin) == HIGH && state == true) {
        state = false;
        return true;
    }
    return false;
}
