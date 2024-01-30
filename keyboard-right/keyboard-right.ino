#include "KeyboardListenner.h"
#include "Keyboard.h"

const int rowLength = 6;
const int colLength = 7;
int rowPins[rowLength] = {9, 4, 8, 6, 7, 5};
int colPins[colLength] = {15, 18, 10, 20, 14, 19, 16};

// TODO: Encapsular essa lógica em um 'KeyboardEmitter', que ficará responsável por receber as layers
// matriciais, gerenciar qual a layer está em vigor, bem como disparar os eventos para o PC. Daí
// integrar ele aqui com através das callbacks (se der, posso tentar pensar em um design mais bonito,
// talvez já não precise mais das callbacks, se o 'KeyboardEmitter' for uma composição dentro do
// Listenner... aí acho q eu teria só mesmo q mudar um pouco os nomes talvez?)

uint8_t keyboardMap[rowLength][colLength] = {
    {KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12},
    {(uint8_t)'7', (uint8_t)'8', (uint8_t)'9', (uint8_t)'0', (uint8_t)'-', (uint8_t)'=', KEY_BACKSPACE},
    {(uint8_t)'y', (uint8_t)'u', (uint8_t)'i', (uint8_t)'o', (uint8_t)'p', KEY_ACUTE_ACCENT, 0},
    {(uint8_t)'h', (uint8_t)'j', (uint8_t)'k', (uint8_t)'l', KEY_CEDIL, KEY_TIL, KEY_KP_ENTER},
    {(uint8_t)'n', (uint8_t)'m', (uint8_t)',', (uint8_t)'.', KEY_SEMICOLON, KEY_FOWARD_SLASH, KEY_RIGHT_SHIFT},
    {0, KEY_SPACE, KEY_LAYER_UP, KEY_RIGHT_ALT, KEY_RIGHT_ALT, KEY_RIGHT_CTRL, KEY_RIGHT_CTRL},
};

void onKeyPress(int r, int c) {
    if (keyboardMap[r][c] != 0) {
        Serial.print("Pressed Native: ");
        Serial.println(keyboardMap[r][c]);
        Keyboard.press(keyboardMap[r][c]);
    }
}

void onKeyRelease(int r, int c) {
    if (keyboardMap[r][c] != 0) {
        Keyboard.release(keyboardMap[r][c]);
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
