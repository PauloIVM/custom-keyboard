#include "Mouse.h"
#include "Keyboard.h"
#include "Joystic.h"

#define BUTTON_1 2
#define BUTTON_2 3
#define BUTTON_3 5

Joystic joysticR = Joystic(A1, A0, 542, 515);
Joystic joysticL = Joystic(A2, A3, 517, 503);
boolean button1Pressed = false;
boolean button2Pressed = false;
boolean button3Pressed = false;

void setup(void) {
  Mouse.begin();
  Keyboard.begin();
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
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
  if (digitalRead(BUTTON_1) == LOW && button1Pressed == false) {
    joysticR.toggleRange();
    button1Pressed = true;
  }
  if (digitalRead(BUTTON_1) == HIGH && button1Pressed == true) {
    button1Pressed = false;
  }
  if (digitalRead(BUTTON_2) == LOW && button2Pressed == false) {
    Mouse.click();
    button2Pressed = true;
  }
  if (digitalRead(BUTTON_2) == HIGH && button2Pressed == true) {
    button2Pressed = false;
  }
  if (digitalRead(BUTTON_3) == LOW && button3Pressed == false) {
    Mouse.click(MOUSE_RIGHT);
    button3Pressed = true;
  }
  if (digitalRead(BUTTON_3) == HIGH && button3Pressed == true) {
    button3Pressed = false;
  }
}
