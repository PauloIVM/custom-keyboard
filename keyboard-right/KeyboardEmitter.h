#include "Keyboard.h"

#ifndef KEYBOARD_EMITTER_H
#define KEYBOARD_EMITTER_H

class KeyboardEmitter {
    public:
        KeyboardEmitter(uint8_t*** layers, int layersLength, uint8_t keyLayerUp, uint8_t keyLayerDown);
        void press(int row, int column);
        void release(int row, int column);
    private:
        uint8_t*** layers;
        int layersLength;
        int layerIndex;
        uint8_t keyLayerUp;
        uint8_t keyLayerDown;
        void decreaseLayerIndex();
        void increaseLayerIndex();
};
#endif
