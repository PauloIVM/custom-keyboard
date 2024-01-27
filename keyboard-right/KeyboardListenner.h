#ifndef KEY_EVENT_TYPE_H
#define KEY_EVENT_TYPE_H
enum KeyEventType {
    pressed,
    released
};
#endif

class KeyboardListenner {
    public:
        KeyboardListenner(int* rowPins, int rowPinsLength, int* colPins, int colPinsLength, void (*onPressCallback)(int r, int c), void (*onReleaseCallback)(int r, int c));
        void scan();
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
