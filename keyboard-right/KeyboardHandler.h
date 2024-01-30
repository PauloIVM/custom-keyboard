#include "KeyboardScanner.h"

#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

struct KeyboardHandlerConfig {
    uint8_t*** layers;
    int layersLength;
    uint8_t keyLayerUp;
    uint8_t keyLayerDown;
    int* rowPins;
    int rowLength;
    int* colPins;
    int colLength;
};

class KeyboardHandler {
    public:
        KeyboardHandler(const KeyboardHandlerConfig& config);
        void exec(void);
        void begin(void);
    private:
        KeyboardScanner scanner;
};
#endif
