#include "KeyboardEmitter.h"

KeyboardEmitter::KeyboardEmitter(uint8_t*** layers, int layersLength, uint8_t keyLayerUp, uint8_t keyLayerDown) {
    this->layers = layers;
    this->layersLength = layersLength;
    this->keyLayerUp = keyLayerUp;
    this->keyLayerDown = keyLayerDown;
    this->layerIndex = 0;
}

KeyboardEmitter::KeyboardEmitter() {
    this->layersLength = 0;
    this->keyLayerUp = 0;
    this->keyLayerDown = 0;
    this->layerIndex = 0;
}

// TODO: Tem um desafio aqui... eu posso acabar pressionando uma tecla em uma layer... trocar de layer,
// e aí eu iria dar o release em outra tecla, o q manteria pressionada pra sempre a tecla da primeira
// layer. Tratar isso depois.
void KeyboardEmitter::press(int row, int column) {
    if(this->layersLength == 0) { return; }
    uint8_t key = layers[this->layerIndex][row][column];
    if (key == this->keyLayerUp) { return; }
    if (key == this->keyLayerDown) { return; }
    if (key != 0) { Keyboard.press(key); }
}

void KeyboardEmitter::release(int row, int column) {
    if(this->layersLength == 0) { return; }
    uint8_t key = layers[this->layerIndex][row][column];
    if (key == this->keyLayerUp) { this->increaseLayerIndex(); }
    else if (key == this->keyLayerDown) { this->decreaseLayerIndex(); }
    else if (key != 0) { Keyboard.release(key); }
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
