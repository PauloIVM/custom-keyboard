#include "KeyboardScanner.h"

#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

struct KeyboardHandlerConfig {
    uint8_t keyLayerUp;
    uint8_t keyLayerDown;
    int* rowPins;
    int* colPins;
};

class KeyboardHandler {
    public:
        template <size_t L_LENGTH, size_t R_LENGTH, size_t C_LENGTH>
        KeyboardHandler(const uint8_t (&layers)[L_LENGTH][R_LENGTH][C_LENGTH], const KeyboardHandlerConfig& configs) {
            uint8_t*** dynamicLayers = this->toDynamicLayers(layers);
            KeyboardEmitter emitter = KeyboardEmitter(
                dynamicLayers,
                L_LENGTH,
                configs.keyLayerUp,
                configs.keyLayerDown
            );
            this->scanner = KeyboardScanner(
                configs.rowPins,
                R_LENGTH,
                configs.colPins,
                C_LENGTH,
                emitter
            );
        }
        void exec(void) { this->scanner.scan(); }
        void begin(void) { Keyboard.begin(); }
    private:
        KeyboardScanner scanner;
        template <size_t L_LENGTH, size_t R_LENGTH, size_t C_LENGTH>
        uint8_t*** toDynamicLayers(const uint8_t (&layers)[L_LENGTH][R_LENGTH][C_LENGTH]) {
            uint8_t*** dynamicMatrix = (uint8_t***)malloc(L_LENGTH * sizeof(uint8_t**));
            for (size_t i = 0; i < L_LENGTH; ++i) {
                dynamicMatrix[i] = (uint8_t**)malloc(R_LENGTH * sizeof(uint8_t*));
                for (size_t row = 0; row < R_LENGTH; ++row) {
                    dynamicMatrix[i][row] = (uint8_t*)malloc(C_LENGTH * sizeof(uint8_t));
                    for (size_t col = 0; col < C_LENGTH; ++col) {
                        dynamicMatrix[i][row][col] = layers[i][row][col];
                    }
                }
            }
            return dynamicMatrix;
        }
};
#endif
