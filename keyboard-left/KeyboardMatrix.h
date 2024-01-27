#ifndef KEY_EVENT_TYPE_H
#define KEY_EVENT_TYPE_H
enum KeyEventType {
    pressed,
    released
};
#endif

class KeyboardMatrix {
    public:
        KeyboardMatrix(int* rowPins, int rowPinsLength, int* colPins, int colPinsLength, void (*onPressCallback)(int r, int c), void (*onReleaseCallback)(int r, int c));
        void printCellsPressed();
    private:
        void fillCols(int value);
        int* rowPins;
        int rowPinsLength;
        int* colPins;
        int colPinsLength;
        int** keysStateMatrix;
        void (*onPressCallback)(int r, int c);
        void (*onReleaseCallback)(int r, int c);
};
