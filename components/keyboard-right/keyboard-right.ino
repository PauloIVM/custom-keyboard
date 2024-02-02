#include <KeyboardHandler.h>

const int rowsLength = 6;
const int colsLength = 7;
const int layersLength = 2;
int rowPins[rowsLength] = {9, 4, 8, 6, 7, 5};
int colPins[colsLength] = {15, 18, 10, 20, 14, 19, 16};

uint8_t layers[layersLength][rowsLength][colsLength] = {
    // INFO: Layer 0
    {
        {KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12},
        {(uint8_t)'7', (uint8_t)'8', (uint8_t)'9', (uint8_t)'0', (uint8_t)'-', (uint8_t)'=', KEY_BACKSPACE},
        {(uint8_t)'y', (uint8_t)'u', (uint8_t)'i', (uint8_t)'o', (uint8_t)'p', KEY_ACUTE_ACCENT, 0},
        {(uint8_t)'h', (uint8_t)'j', (uint8_t)'k', (uint8_t)'l', KEY_CEDIL, KEY_TIL, KEY_KP_ENTER},
        {KEY_FOWARD_SLASH, (uint8_t)'n', (uint8_t)'m', (uint8_t)',', (uint8_t)'.', KEY_SEMICOLON, KEY_RIGHT_SHIFT},
        {0, KEY_RIGHT_CTRL, KEY_LAYER_UP, KEY_RIGHT_ALT, KEY_RIGHT_ALT, KEY_RIGHT_CTRL, KEY_RIGHT_CTRL},
    },
    // INFO: Layer 1
    {
        {KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12},
        {(uint8_t)'7', (uint8_t)'8', (uint8_t)'9', (uint8_t)'0', (uint8_t)'-', (uint8_t)'=', KEY_BACKSPACE},
        {KEY_PAGE_UP, KEY_HOME, KEY_UP_ARROW, KEY_END, KEY_DELETE, KEY_ACUTE_ACCENT, 0},
        {KEY_PAGE_DOWN, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_CEDIL, KEY_TIL, KEY_KP_ENTER},
        {KEY_FOWARD_SLASH, (uint8_t)'n', (uint8_t)'m', (uint8_t)',', (uint8_t)'.', KEY_SEMICOLON, KEY_RIGHT_SHIFT},
        {0, KEY_RIGHT_CTRL, KEY_LAYER_UP, KEY_RIGHT_ALT, KEY_RIGHT_ALT, KEY_RIGHT_CTRL, KEY_RIGHT_CTRL},
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
    keyboardHandler.begin();
}

void loop(void) {
    keyboardHandler.exec();
}
