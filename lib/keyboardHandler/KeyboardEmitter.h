#include "Keyboard.h"

#ifndef KEYBOARD_EMITTER_H
#define KEYBOARD_EMITTER_H

#define KEY_LAYER_UP      0x10
#define KEY_LAYER_DOWN    0x11
#define KEY_LAYER_1       0x01
#define KEY_LAYER_2       0x02
#define KEY_LAYER_3       0x03
#define KEY_LAYER_4       0x04
#define KEY_LAYER_5       0x05
#define KEY_LAYER_6       0x06
#define KEY_LAYER_7       0x07
#define KEY_LAYER_8       0x08
#define KEY_LAYER_9       0x09

class KeyboardEmitter {
    public:
        KeyboardEmitter();
        KeyboardEmitter(uint8_t*** layers, int layersLength);
        void press(int row, int column);
        void release(int row, int column);
    private:
        uint8_t*** layers;
        int layersLength;
        int layerIndex;
        void decreaseLayerIndex();
        void increaseLayerIndex();
        bool isLayerIndex(uint8_t key);
};
#endif
