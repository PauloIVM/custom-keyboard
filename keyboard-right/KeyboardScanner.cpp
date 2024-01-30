#include "KeyboardScanner.h"
#include "Arduino.h"

KeyboardScanner::KeyboardScanner(int* rowPins, int rowLength, int* colPins, int colLength, void (*onPressCallback)(int r, int c), void (*onReleaseCallback)(int r, int c)) {
    this->rowPins = rowPins;
    this->rowLength = rowLength;
    this->colPins = colPins;
    this->colLength = colLength;
    this->onPressCallback = onPressCallback;
    this->onReleaseCallback = onReleaseCallback;
    this->keysStateMatrix = (int**)malloc(rowLength * sizeof(int*));
    for (int i = 0; i < rowLength; ++i) {
        this->keysStateMatrix[i] = (int*)malloc(colLength * sizeof(int));
    }
    for (int i = 0; i < rowLength; ++i) {
        for (int j = 0; j < colLength; ++j) {
            this->keysStateMatrix[i][j] = HIGH;
        }
    }
}

void KeyboardScanner::scan() {
    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++) {
        fillCols(HIGH);
        for (int colIndex = 0; colIndex < colLength; colIndex++) {
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
    // INFO: This delay avoid double-clicks
    delay(20);
}

void KeyboardScanner::fillCols(int value) {
    for (int i = 0; i < this->colLength; i++) {
        digitalWrite(this->colPins[i], value);
    }
}
