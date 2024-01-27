#include "KeyboardListenner.h"
#include "Keyboard.h"

const int rowLength = 6;
const int colLength = 7;
int rowPins[rowLength] = {9, 4, 8, 6, 7, 5};
int colPins[colLength] = {15, 18, 10, 20, 14, 19, 16};

// TODO: Talvez inverter a ordem do 'colPins' pro desenho do keyboardMap não ficar
// rotacionado ou espelhado.
uint8_t keyboardMap[rowLength][colLength] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {(uint8_t)'y', (uint8_t)'u', (uint8_t)'i', (uint8_t)'o', (uint8_t)'p', (uint8_t)'\'', 0},
    {0, 0, 0, 0, 0, 0, KEY_KP_ENTER},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
};

void onKeyPress(int r, int c) {
    if (keyboardMap[r][c] != 0) {
        Serial.println("Pressed Native");
        Keyboard.press(keyboardMap[r][c]);
    } else {
        Serial.print("[ R: ");
        Serial.print(r, DEC);
        Serial.print(", C: ");
        Serial.print(c, DEC);
        Serial.println(" ] Pressed");
    }
}

void onKeyRelease(int r, int c) {
    if (keyboardMap[r][c] != 0) {
        Serial.println("Released Native");
        Keyboard.release(keyboardMap[r][c]);
    } else {
        Serial.print("[ R: ");
        Serial.print(r, DEC);
        Serial.print(", C: ");
        Serial.print(c, DEC);
        Serial.println(" ] Released");
    }
}

KeyboardListenner keyboardListenner = KeyboardListenner(rowPins, rowLength, colPins, colLength, onKeyPress, onKeyRelease);

void setup(void) {
    Serial.begin(9600);
    Keyboard.begin();
    setPinModes(colPins, OUTPUT,        colLength);
    setPinModes(rowPins, INPUT_PULLUP,  rowLength);
}

void loop(void) {
    keyboardListenner.scan();
}

void setPinModes(int pins[], int mode, int length) {
    for (int i = 0; i < length; i++) {
        pinMode(pins[i], mode);
    }
}
