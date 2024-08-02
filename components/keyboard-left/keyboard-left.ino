#include <KeyboardHandler.h>
#include <Mouse.h>
#include <Button.h>
#include <Joystic.h>

void onButtonPress(void) {
    Mouse.press(MOUSE_RIGHT);
}

void onButtonRelease(void) {
    Mouse.release(MOUSE_RIGHT);
}

Button button = Button(2, onButtonPress, onButtonRelease);

void onChangeJoystic(int x, int y) {
    Mouse.move(-x, y, 0);
}

Joystic joystic = Joystic(A2, A3, 517, 506, onChangeJoystic);

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
        {KEY_WINDOWS, KEY_BACKSLASH, (uint8_t)'z', (uint8_t)'x', (uint8_t)'c', (uint8_t)'v', (uint8_t)'b'},
        {KEY_UNKNOWN, KEY_UNKNOWN, 0, KEY_LEFT_ALT, KEY_LEFT_SHIFT, 0, KEY_SPACE},
    },
};

KeyboardHandler<layersLength, rowsLength, colsLength> keyboardHandler(layers, rowPins, colPins);

void setup(void) {
    keyboardHandler.begin();
    Mouse.begin();
    button.begin();
}

void loop(void) {
    keyboardHandler.exec();
    button.exec();
    joystic.exec();
}
