#include "KeyboardEmitter.h"

KeyboardEmitter::KeyboardEmitter(uint8_t*** layers, int layersLength) {
    this->layers = layers;
    this->layersLength = layersLength;
    this->layerIndex = 0;
}

KeyboardEmitter::KeyboardEmitter() {
    this->layersLength = 0;
    this->layerIndex = 0;
}

// TODO: Tem um desafio aqui... eu posso acabar pressionando uma tecla em uma layer... trocar de layer,
// e aí eu iria dar o release em outra tecla, o q manteria pressionada pra sempre a tecla da primeira
// layer. Tratar isso depois.
void KeyboardEmitter::press(int row, int column) {
    if(this->layersLength == 0) { return; }
    uint8_t key = layers[this->layerIndex][row][column];
    if (key == KEY_LAYER_UP) { return; }
    if (key == KEY_LAYER_DOWN) { return; }
    if (this->isLayerIndex(key)) { return; }
    if (key != 0) { Keyboard.press(key); }
}

void KeyboardEmitter::release(int row, int column) {
    if(this->layersLength == 0) { return; }
    uint8_t key = layers[this->layerIndex][row][column];
    if (key == KEY_LAYER_UP) { this->increaseLayerIndex(); }
    else if (key == KEY_LAYER_DOWN) { this->decreaseLayerIndex(); }
    else if (this->isLayerIndex(key)) { this->layerIndex = key - 1; }
    else if (key != 0) { Keyboard.release(key); }
}

bool KeyboardEmitter::isLayerIndex(uint8_t key) {
    if (
        key == KEY_LAYER_1 ||
        key == KEY_LAYER_2 ||
        key == KEY_LAYER_3 ||
        key == KEY_LAYER_4 ||
        key == KEY_LAYER_5 ||
        key == KEY_LAYER_6 ||
        key == KEY_LAYER_7 ||
        key == KEY_LAYER_8 ||
        key == KEY_LAYER_9
    ) {
        return true;
    }
    return false;
}

void KeyboardEmitter::decreaseLayerIndex() {
    if (this->layerIndex > 0) {
        this->layerIndex--;
        return;
    }
    this->layerIndex = this->layersLength - 1;
}

void KeyboardEmitter::increaseLayerIndex() {
    if (this->layerIndex < this->layersLength - 1) {
        this->layerIndex++;
        return;
    }
    this->layerIndex = 0;
}
