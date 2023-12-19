#include "Button.h"
#include "Arduino.h"

Button::Button(int pin) {
    this->pin = pin;
    this->pressed = false;
}

bool Button::clicked(void) {
    if (digitalRead(pin) == LOW && pressed == false) {
        pressed = true;
        return true;
    }
    if (digitalRead(pin) == HIGH && pressed == true) {
        pressed = false;
    }
    return false;
}
