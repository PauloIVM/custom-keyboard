#include "KeyboardEmitter.h"

#ifndef KEYBOARD_LISTENNER_H
#define KEYBOARD_LISTENNER_H

#define KEY_UNKNOWN       0x00
#define KEY_CEDIL         0x3B
#define KEY_TIL           0x27
#define KEY_SEMICOLON     0x2F
#define KEY_ACUTE_ACCENT  0x5B
#define KEY_RS_BRACKET    0x5C
#define KEY_RC_BRACKET    0x7C
#define KEY_LS_BRACKET    0x5D
#define KEY_GRAVE_ACCENT  0x7B
#define KEY_LC_BRACKET    0x7D
#define KEY_APOSTROPHE    0x60
#define KEY_BREAKPOINT    0xCA
#define KEY_BACKSLASH     0xEC
#define KEY_FOWARD_SLASH  0xDC
#define KEY_SPACE         0xB4
#define KEY_WINDOWS       0x83

enum KeyEventType {
    pressed,
    released
};

class KeyboardScanner {
    public:
        KeyboardScanner(int* rowPins, int rowsLength, int* colPins, int colsLength, const KeyboardEmitter& emitter);
        KeyboardScanner();
        void scan();
    private:
        void fillCols(int value);
        bool hasKeyToRelease(int rowIndex);
        bool hasKeyToPress(int rowIndex);
        int* rowPins;
        int rowsLength;
        int* colPins;
        int colsLength;
        int** keysStateMatrix;
        KeyboardEmitter emitter;
};
#endif
