#include "KeyboardMatrix.h"
#include "Arduino.h"

KeyboardMatrix::KeyboardMatrix(int* rowPins, int rowPinsLength, int* colPins, int colPinsLength) {
    this->rowPins = rowPins;
    this->rowPinsLength = rowPinsLength;
    this->colPins = colPins;
    this->colPinsLength = colPinsLength;
    // TODO: Refatorar para q essa config de max 100 keys não fique hard-coded
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            keysStateMatrix[i][j] = HIGH;
        }
    }
}

void KeyboardMatrix::printCellsPressed() {
    for (int rowIndex = 0; rowIndex < rowPinsLength; rowIndex++) {
        fillCols(HIGH);
        for (int colIndex = 0; colIndex < colPinsLength; colIndex++) {
            if (colIndex != 0) digitalWrite(colPins[colIndex - 1], HIGH);
            digitalWrite(colPins[colIndex], LOW);
            if (digitalRead(rowPins[rowIndex]) == LOW && keysStateMatrix[rowIndex][colIndex] == HIGH) {
                Serial.print("[ Row: ");
                Serial.print(rowIndex, DEC);
                Serial.print(", Col: ");
                Serial.print(colIndex, DEC);
                Serial.println(" ] Pressed");
                keysStateMatrix[rowIndex][colIndex] = LOW;
            }
            if (digitalRead(rowPins[rowIndex]) == HIGH && keysStateMatrix[rowIndex][colIndex] == LOW) {
                Serial.print("[ Row: ");
                Serial.print(rowIndex, DEC);
                Serial.print(", Col: ");
                Serial.print(colIndex, DEC);
                Serial.println(" ] Released");
                keysStateMatrix[rowIndex][colIndex] = HIGH;
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
