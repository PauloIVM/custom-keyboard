#include "KeyboardListenner.h"
#include "Arduino.h"

KeyboardListenner::KeyboardListenner(int* rowPins, int rowPinsLength, int* colPins, int colPinsLength, void (*onPressCallback)(int r, int c), void (*onReleaseCallback)(int r, int c)) {
    this->rowPins = rowPins;
    this->rowPinsLength = rowPinsLength;
    this->colPins = colPins;
    this->colPinsLength = colPinsLength;
    this->onPressCallback = onPressCallback;
    this->onReleaseCallback = onReleaseCallback;
    this->keysStateMatrix = (int**)malloc(rowPinsLength * sizeof(int*));
    for (int i = 0; i < rowPinsLength; ++i) {
        this->keysStateMatrix[i] = (int*)malloc(colPinsLength * sizeof(int));
    }
    for (int i = 0; i < rowPinsLength; ++i) {
        for (int j = 0; j < colPinsLength; ++j) {
            this->keysStateMatrix[i][j] = HIGH;
        }
    }
}

void KeyboardListenner::scan() {
    for (int rowIndex = 0; rowIndex < rowPinsLength; rowIndex++) {
        fillCols(HIGH);
        for (int colIndex = 0; colIndex < colPinsLength; colIndex++) {
            if (colIndex != 0) digitalWrite(colPins[colIndex - 1], HIGH);
            digitalWrite(colPins[colIndex], LOW);
            if (digitalRead(rowPins[rowIndex]) == LOW && keysStateMatrix[rowIndex][colIndex] == HIGH) {
                this->onPressCallback(rowIndex, colIndex);
                keysStateMatrix[rowIndex][colIndex] = LOW;
            }
            if (digitalRead(rowPins[rowIndex]) == HIGH && keysStateMatrix[rowIndex][colIndex] == LOW) {
                this->onReleaseCallback(rowIndex, colIndex);
                keysStateMatrix[rowIndex][colIndex] = HIGH;
            }
        }
        fillCols(LOW);
    }
}

void KeyboardListenner::fillCols(int value) {
    for (int i = 0; i < this->colPinsLength; i++) {
        digitalWrite(this->colPins[i], value);
    }
}
