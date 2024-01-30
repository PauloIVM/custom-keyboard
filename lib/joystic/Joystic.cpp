#include "Joystic.h"
#include "Arduino.h"
#include "pins_arduino.h"

Joystic::Joystic(int xPin, int yPin, int xAnalogCenter, int yAnalogCenter) {
    this->xPin = xPin;
    this->yPin = yPin;
    this->xAnalogCenter = xAnalogCenter;
    this->yAnalogCenter = yAnalogCenter;
    this->threshold = 10;
    this->range = 40;
}

void Joystic::toggleRange(void) {
    if (range == 40) { range = 10; }
    else { range = 40; }
}

void Joystic::setRange(int range) {
    this->range = range;
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
        return -reading;
    }
    if (reading >= borderUp) {
        reading = map(reading, borderUp, 1023, 0, range);
        return -reading;
    }
    return 0;
}
