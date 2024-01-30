#include "KeyboardHandler.h"

const int rowLength = 6;
const int colLength = 7;
const int layersLength = 2;
int rowPins[rowLength] = {9, 4, 8, 6, 7, 5};
int colPins[colLength] = {15, 18, 10, 20, 14, 19, 16};

uint8_t staticLayers[layersLength][rowLength][colLength] = {
    // INFO: Layer 0
    {
        {KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12},
        {(uint8_t)'7', (uint8_t)'8', (uint8_t)'9', (uint8_t)'0', (uint8_t)'-', (uint8_t)'=', KEY_BACKSPACE},
        {(uint8_t)'y', (uint8_t)'u', (uint8_t)'i', (uint8_t)'o', (uint8_t)'p', KEY_ACUTE_ACCENT, 0},
        {(uint8_t)'h', (uint8_t)'j', (uint8_t)'k', (uint8_t)'l', KEY_CEDIL, KEY_TIL, KEY_KP_ENTER},
        {(uint8_t)'n', (uint8_t)'m', (uint8_t)',', (uint8_t)'.', KEY_SEMICOLON, KEY_FOWARD_SLASH, KEY_RIGHT_SHIFT},
        {0, KEY_SPACE, KEY_LAYER_UP, KEY_RIGHT_ALT, KEY_RIGHT_ALT, KEY_RIGHT_CTRL, KEY_RIGHT_CTRL},
    },
    // INFO: Layer 1
    {
        {KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12},
        {(uint8_t)'7', (uint8_t)'8', (uint8_t)'9', (uint8_t)'0', (uint8_t)'-', (uint8_t)'=', KEY_BACKSPACE},
        {(uint8_t)'y', (uint8_t)'u', KEY_UP_ARROW, (uint8_t)'o', (uint8_t)'p', KEY_ACUTE_ACCENT, 0},
        {(uint8_t)'h', KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_CEDIL, KEY_TIL, KEY_KP_ENTER},
        {(uint8_t)'n', (uint8_t)'m', (uint8_t)',', (uint8_t)'.', KEY_SEMICOLON, KEY_FOWARD_SLASH, KEY_RIGHT_SHIFT},
        {0, KEY_SPACE, KEY_LAYER_UP, KEY_RIGHT_ALT, KEY_RIGHT_ALT, KEY_RIGHT_CTRL, KEY_RIGHT_CTRL},
    },
};

// TODO: Eu queria conseguir fazer um casting ou algo mais simples, mas n funcionou bem. Parece q
// em C++ existe uma forma de fazer isso, pesquisar por: template <size_t Rows, size_t Cols>, daí
// depois voltar aqui e eliminar a necessidade de ficar passando essas matrizes dinâmicas.
uint8_t*** convertStaticLayersToDynamic(uint8_t staticMatrix[rowLength][rowLength][colLength], size_t numLayers, size_t numRows, size_t numCols);

uint8_t*** layers = convertStaticLayersToDynamic(staticLayers, layersLength, rowLength, colLength);

KeyboardHandlerConfig configs = {
    layers,
    layersLength,
    KEY_LAYER_UP,
    KEY_LAYER_DOWN,
    rowPins,
    rowLength,
    colPins,
    colLength
};

KeyboardHandler keyboardHandler = KeyboardHandler(configs);

void setup(void) {
    Serial.begin(9600);
    keyboardHandler.begin();
    setPinModes(colPins, OUTPUT,        colLength);
    setPinModes(rowPins, INPUT_PULLUP,  rowLength);
}

void loop(void) {
    keyboardHandler.exec();
}

void setPinModes(int pins[], int mode, int length) {
    for (int i = 0; i < length; i++) {
        pinMode(pins[i], mode);
    }
}

uint8_t*** convertStaticLayersToDynamic(uint8_t staticMatrix[rowLength][rowLength][colLength], size_t numLayers, size_t numRows, size_t numCols) {
    uint8_t*** dynamicMatrix = (uint8_t***)malloc(numLayers * sizeof(uint8_t**));
    for (size_t i = 0; i < numLayers; ++i) {
        dynamicMatrix[i] = (uint8_t**)malloc(numRows * sizeof(uint8_t*));
        for (size_t row = 0; row < numRows; ++row) {
            dynamicMatrix[i][row] = (uint8_t*)malloc(numCols * sizeof(uint8_t));
            for (size_t col = 0; col < numCols; ++col) {
                dynamicMatrix[i][row][col] = staticMatrix[i][row][col];
            }
        }
    }
    return dynamicMatrix;
}
