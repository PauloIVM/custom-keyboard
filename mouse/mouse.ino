#include "Mouse.h"
#include "Keyboard.h"
#include "Button.h"
#include "Joystic.h"

#define BUTTON_LEFT_PIN 2
#define BUTTON_MID_PIN 3
#define BUTTON_RIGHT_PIN 5

Joystic joysticR = Joystic(A1, A0, 542, 515);
Joystic joysticL = Joystic(A2, A3, 517, 503);
Button ButtonL = Button(BUTTON_LEFT_PIN);
Button ButtonM = Button(BUTTON_MID_PIN);
Button ButtonR = Button(BUTTON_RIGHT_PIN);

void setup(void) {
    Mouse.begin();
    Keyboard.begin();
    pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_MID_PIN, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
    joysticL.setRange(2);
}

void loop(void) {
    int x = joysticR.readX();
    int y = joysticR.readY();
    int yWheel = joysticL.readY();
    int xWheel = joysticL.readX();
    Mouse.move(x, y, -yWheel);
    delay(30);
    if (xWheel != 0) {
        Keyboard.press(KEY_LEFT_SHIFT);
        Mouse.move(x, y, -xWheel);
        Keyboard.releaseAll();
    }
    if (ButtonL.clicked()) { Mouse.click(); }
    if (ButtonM.clicked()) { Mouse.click(MOUSE_RIGHT); }
    if (ButtonR.clicked()) { joysticR.toggleRange(); }
}