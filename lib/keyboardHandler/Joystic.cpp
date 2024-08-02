#include "Joystic.h"
#include "Arduino.h"
#include "pins_arduino.h"

Joystic::Joystic(int xPin, int yPin, int xAnalogCenter, int yAnalogCenter) {
    this->xPin = xPin;
    this->yPin = yPin;
    this->xAnalogCenter = xAnalogCenter;
    this->yAnalogCenter = yAnalogCenter;
    this->threshold = 5;
    this->range = 40;
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
        // if (reading >= borderDown - 300) {
        //     reading = borderDown - range - range;
        // }
        // INFO: Talvez o que eu queira seja: se a pessoa pregar o dedo no máximo, incrementar
        //       baseado no tempo.
        // INFO: De qualquer forma, parece mais simples eu "reduzir" o reading pra tudo e aumentar
        //       apenas se estiver no máximo.
        // INFO: Uma transposição suavizada poderia ser algo como:
        // 10 50 100 150 200 250 300 350 400 450 500
        //  5 25  50 100 150 200 250 300 400 450 500
        reading = map(reading, borderDown, 0, 0, -range);

        return -reading/2;
    }
    if (reading >= borderUp) {
        // if (reading <= borderUp + 300) {
        //     reading = borderUp + range + range;
        // }
        reading = map(reading, borderUp, 1023, 0, range);
        return -reading/2;
    }
    return 0;
}
