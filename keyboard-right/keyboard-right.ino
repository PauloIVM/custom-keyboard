#include "KeyboardListenner.h"

int rowPins[6] = {9, 4, 8, 6, 7, 5};
int colPins[7] = {16, 19, 14, 20, 10, 18, 15};

int rowPinsLength = sizeof(rowPins) / sizeof(rowPins[0]);
int colPinsLength = sizeof(colPins) / sizeof(colPins[0]);

void onKeyPress(int r, int c) {
    Serial.print("[ R: ");
    Serial.print(r, DEC);
    Serial.print(", C: ");
    Serial.print(c, DEC);
    Serial.println(" ] Pressed");
}

void onKeyRelease(int r, int c) {
    Serial.print("[ R: ");
    Serial.print(r, DEC);
    Serial.print(", C: ");
    Serial.print(c, DEC);
    Serial.println(" ] Released");
}

KeyboardListenner keyboardListenner = KeyboardListenner(rowPins, rowPinsLength, colPins, colPinsLength, onKeyPress, onKeyRelease);

void setup(void) {
    Serial.begin(9600);
    setPinModes(colPins, OUTPUT,        colPinsLength);
    setPinModes(rowPins, INPUT_PULLUP,  rowPinsLength);
}

void loop(void) {
    keyboardListenner.scan();
}

void setPinModes(int pins[], int mode, int length) {
    for (int i = 0; i < length; i++) {
        pinMode(pins[i], mode);
    }
}
