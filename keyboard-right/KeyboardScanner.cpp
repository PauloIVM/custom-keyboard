#include "KeyboardScanner.h"

KeyboardScanner::KeyboardScanner(int* rowPins, int rowsLength, int* colPins, int colsLength, const KeyboardEmitter& emitter) {
    this->rowPins = rowPins;
    this->rowsLength = rowsLength;
    this->colPins = colPins;
    this->colsLength = colsLength;
    this->emitter = emitter;
    this->keysStateMatrix = (int**)malloc(rowsLength * sizeof(int*));
    for (int i = 0; i < rowsLength; ++i) {
        this->keysStateMatrix[i] = (int*)malloc(colsLength * sizeof(int));
    }
    for (int i = 0; i < rowsLength; ++i) {
        for (int j = 0; j < colsLength; ++j) {
            this->keysStateMatrix[i][j] = HIGH;
        }
    }
}

KeyboardScanner::KeyboardScanner() {
    this->rowsLength = 0;
    this->colsLength = 0;
}

void KeyboardScanner::scan() {
    if (this->rowsLength == 0 || this->colsLength == 0) { return; }
    for (int rowIndex = 0; rowIndex < rowsLength; rowIndex++) {
        fillCols(HIGH);
        for (int colIndex = 0; colIndex < colsLength; colIndex++) {
            if (colIndex != 0) digitalWrite(colPins[colIndex - 1], HIGH);
            digitalWrite(colPins[colIndex], LOW);
            if (digitalRead(rowPins[rowIndex]) == LOW && keysStateMatrix[rowIndex][colIndex] == HIGH) {
                this->emitter.press(rowIndex, colIndex);
                keysStateMatrix[rowIndex][colIndex] = LOW;
            }
            if (digitalRead(rowPins[rowIndex]) == HIGH && keysStateMatrix[rowIndex][colIndex] == LOW) {
                this->emitter.release(rowIndex, colIndex);
                keysStateMatrix[rowIndex][colIndex] = HIGH;
            }
        }
        fillCols(LOW);
    }
    // INFO: This delay avoid double-clicks
    delay(20);
}

void KeyboardScanner::fillCols(int value) {
    for (int i = 0; i < this->colsLength; i++) {
        digitalWrite(this->colPins[i], value);
    }
}
