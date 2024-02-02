#include <KeyboardHandler.h>

const int rowsLength = 6;
const int colsLength = 7;
const int layersLength = 2;
int rowPins[rowsLength] = {19, 18, 10, 16, 15, 14};
int colPins[colsLength] = {5, 9, 3, 7, 4, 8, 6};

uint8_t layers[layersLength][rowsLength][colsLength] = {
    // INFO: Layer 0
    {
        {KEY_ESC, 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5},
        {KEY_APOSTROPHE, (uint8_t)'1', (uint8_t)'2', (uint8_t)'3', (uint8_t)'4', (uint8_t)'5', (uint8_t)'6'},
        {KEY_TAB, (uint8_t)'q', (uint8_t)'w', (uint8_t)'e', (uint8_t)'r', (uint8_t)'t', KEY_LS_BRACKET},
        {KEY_CAPS_LOCK, (uint8_t)'a', (uint8_t)'s', (uint8_t)'d', (uint8_t)'f', (uint8_t)'g', KEY_RS_BRACKET},
        {KEY_LEFT_SHIFT, KEY_BACKSLASH, (uint8_t)'z', (uint8_t)'x', (uint8_t)'c', (uint8_t)'v', (uint8_t)'b'},
        {KEY_LAYER_UP, (uint8_t)'m', 0, KEY_MENU, KEY_LEFT_ALT, 0, KEY_SPACE},
    },
};

KeyboardHandlerConfig configs = {
    KEY_LAYER_UP,
    KEY_LAYER_DOWN,
    rowPins,
    colPins,
};

KeyboardHandler<layersLength, rowsLength, colsLength> keyboardHandler(layers, configs);

void setup(void) {
    Serial.begin(9600);
    keyboardHandler.begin();
}

void loop(void) {
    keyboardHandler.exec();
}
