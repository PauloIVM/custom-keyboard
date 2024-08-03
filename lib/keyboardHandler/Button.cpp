#include "Button.h"
#include "Arduino.h"

Button::Button(int pin, void (*onPress)(void), void (*onRelease)(void)) {
    this->pin = pin;
    this->state = false;
    this->onPress = onPress;
    this->onRelease = onRelease;
}

void Button::begin(void) {
    pinMode(this->pin, INPUT_PULLUP);
}

void Button::exec(void) {
    if (pressed()) {
        onPress();
    }
    if (released()) {
        onRelease();
    }
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
