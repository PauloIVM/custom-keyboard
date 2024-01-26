int rowPins[6] = {9, 4, 8, 6, 7, 5};
int colPins[7] = {16, 19, 14, 20, 10, 18, 15};

int rowPinsLength = sizeof(rowPins) / sizeof(rowPins[0]);
int colPinsLength = sizeof(colPins) / sizeof(colPins[0]);

void setup(void) {
    Serial.begin(9600);
    setPinModes(colPins, OUTPUT,        colPinsLength);
    setPinModes(rowPins, INPUT_PULLUP,  rowPinsLength);
    Serial.print("Size: ");
    Serial.println(sizeof(colPins), DEC);
    fillCols(LOW);
}

void loop(void) {
    int length = sizeof(rowPins) / sizeof(rowPins[0]);
    for (int rowIndex = 0; rowIndex < length; rowIndex++) {
        getCellsPressedAtRow(rowIndex);
    }
}

// TODO: Melhor passar uma callback? Ou retornar um valor?? Tenho q pensar q devo precisar monitorar o release, para teclas
// como o ctrl e etc.
void getCellsPressedAtRow(int rowIndex) {
    fillCols(HIGH);
    for (int colIndex = 0; colIndex < colPinsLength; colIndex++) {
        if (colIndex != 0) digitalWrite(colPins[colIndex - 1], HIGH);
        digitalWrite(colPins[colIndex], LOW);
        if (digitalRead(rowPins[rowIndex]) == LOW) {
            Serial.print("[ Row: ");
            Serial.print(rowIndex, DEC);
            Serial.print(", Col: ");
            Serial.print(colIndex, DEC);
            Serial.println(" ]");
        }
    }
    fillCols(LOW);
}

void fillCols(int value) {
    for (int i = 0; i < colPinsLength; i++) {
        digitalWrite(colPins[i], value);
    }
}

void setPinModes(int pins[], int mode, int length) {
    for (int i = 0; i < length; i++) {
        pinMode(pins[i], mode);
    }
}
