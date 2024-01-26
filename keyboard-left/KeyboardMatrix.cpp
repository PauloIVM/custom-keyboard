#include "KeyboardMatrix.h"
#include "Arduino.h"

KeyboardMatrix::KeyboardMatrix(int* rowPins, int rowPinsLength, int* colPins, int colPinsLength) {
    this->rowPins = rowPins;
    this->rowPinsLength = rowPinsLength;
    this->colPins = colPins;
    this->colPinsLength = colPinsLength;
}

void KeyboardMatrix::printCellsPressed() {
    for (int rowIndex = 0; rowIndex < rowPinsLength; rowIndex++) {
        fillCols(HIGH);
        for (int colIndex = 0; colIndex < colPinsLength; colIndex++) {
            if (colIndex != 0) digitalWrite(colPins[colIndex - 1], HIGH);
            digitalWrite(colPins[colIndex], LOW);
            if (digitalRead(rowPins[rowIndex]) == LOW) {
                Serial.print("[ Rowz: ");
                Serial.print(rowIndex, DEC);
                Serial.print(", Cols: ");
                Serial.print(colIndex, DEC);
                Serial.println(" ]");
            }
        }
        fillCols(LOW);
    }
}

void KeyboardMatrix::fillCols(int value) {
    for (int i = 0; i < this->colPinsLength; i++) {
        digitalWrite(this->colPins[i], value);
    }
}
