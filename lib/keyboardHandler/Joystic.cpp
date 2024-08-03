#include "Joystic.h"
#include "Arduino.h"
#include "pins_arduino.h"
// #include <stdio.h>

Joystic::Joystic(int xPin, int yPin, int xAnalogCenter, int yAnalogCenter, void (*onChange)(int x, int y)) {
    this->xPin = xPin;
    this->yPin = yPin;
    this->xAnalogCenter = xAnalogCenter;
    this->yAnalogCenter = yAnalogCenter;
    this->onChange = onChange;
    this->threshold = 5;
    this->range = 40;
}

void Joystic::setRange(int range) {
    this->range = range;
}

void Joystic::exec(void) {
    int x = readX();
    int y = readY();
    onChange(x, y);
}

int Joystic::readX(void) {
    int result = this->read(xPin, xAnalogCenter); 
    return result;
}

int Joystic::readY(void) {
    int result = this->read(yPin, yAnalogCenter); 
    return result;
}

int Joystic::read(int pin, int analogCenter) {
    int distance = 0;
    int reading = analogRead(pin);
    int borderDown = analogCenter - threshold;
    int borderUp = analogCenter + threshold;
    if (reading <= borderDown) {
        reading = map(reading, borderDown, 0, 0, -range);
        // TODO: Ao invés de callbacks, usar o pattern template... e aí a func de sensibilidade
        //       deverá ser sobrescrita pelo classe que implementa essa, que passará a ser uma
        //       classe abstrata. 
        // int sensb = abs(reading) > range / 2 ? 2 : 4;
        return -reading/2;
    }
    if (reading >= borderUp) {
        reading = map(reading, borderUp, 1023, 0, range);
        // int sensb = abs(reading) > range / 2 ? 2 : 4;
        return -reading/2;
    }
    return 0;
}
