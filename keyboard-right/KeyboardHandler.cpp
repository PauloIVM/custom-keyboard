#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler(const KeyboardHandlerConfig& config) {
    KeyboardEmitter emitter = KeyboardEmitter(config.layers, config.layersLength, config.keyLayerUp, config.keyLayerDown);
    this->scanner = KeyboardScanner(config.rowPins, config.rowLength, config.colPins, config.colLength, emitter);
}

void KeyboardHandler::exec() {
    this->scanner.scan();
}

void KeyboardHandler::begin() {
    Keyboard.begin();
}
