#include "KeyboardListenner.h"
#include "Keyboard.h"

const int rowLength = 6;
const int colLength = 7;
int rowPins[rowLength] = {9, 4, 8, 6, 7, 5};
int colPins[colLength] = {15, 18, 10, 20, 14, 19, 16};

// TODO: Mapear todas as teclas. Q protocolo é esse em específico? Como saber o inteiro
// referente a cada tecla? Pesquisar no chatGPT e usar a diretiva "#define" pra cada uma das
// teclas q não está mapeada no "Keyboard.h"
/**
 * (uint8_t)';' = 'ç'
 * (uint8_t)'ç' = 2
 * (uint8_t)'\'' = ~
 * (uint8_t)'/' = ;
 * 
*/

uint8_t keyboardMap[rowLength][colLength] = {
    {0, 0, 0, 0, 0, 0, 0},
    {(uint8_t)'7', (uint8_t)'8', (uint8_t)'9', (uint8_t)'0', (uint8_t)'-', (uint8_t)'=', KEY_BACKSPACE},
    {(uint8_t)'y', (uint8_t)'u', (uint8_t)'i', (uint8_t)'o', (uint8_t)'p', 0, 0},
    {(uint8_t)'h', (uint8_t)'j', (uint8_t)'k', (uint8_t)'l', (uint8_t)';', (uint8_t)'\'', KEY_KP_ENTER},
    {(uint8_t)'n', (uint8_t)'m', (uint8_t)',', (uint8_t)'.', (uint8_t)'/', 0, KEY_RIGHT_SHIFT},
    {0, 0, 0, KEY_RIGHT_ALT, 0, 0, KEY_RIGHT_CTRL},
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
