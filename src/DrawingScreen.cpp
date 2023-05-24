#include "DrawingScreen.h"
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "Arduino.h"
#include "pins_arduino.h"
#include "configs.h"

DrawingScreen::DrawingScreen(MCUFRIEND_kbv *tft, TouchScreen *ts) {
    this->tft = tft;
    this->ts = ts;
    this->currentcolor = configs.RED;
    this->messageManager = MessageManager();
}

void DrawingScreen::loadScreen(void) {
    int16_t boxSize = getBoxSize();
    this->tft->fillScreen(configs.BLACK);
    this->tft->fillRect(0, 0, boxSize, boxSize, configs.RED);
    this->tft->fillRect(boxSize, 0, boxSize, boxSize, configs.YELLOW);
    this->tft->fillRect(boxSize * 2, 0, boxSize, boxSize, configs.GREEN);
    this->tft->fillRect(boxSize * 3, 0, boxSize, boxSize, configs.CYAN);
    this->tft->fillRect(boxSize * 4, 0, boxSize, boxSize, configs.BLUE);
    this->tft->fillRect(boxSize * 5, 0, boxSize, boxSize, configs.MAGENTA);
    this->tft->drawRect(0, 0, boxSize, boxSize, configs.WHITE);
}

void DrawingScreen::showScreen() {
    uint16_t xpos, ypos;
    int16_t boxSize = this->getBoxSize();
    int16_t PENRADIUS = 1;
    TSPoint tp = this->ts->getPoint();
    pinMode(configs.XM, OUTPUT);
    pinMode(configs.YP, OUTPUT);

    if (!(tp.z > configs.MINPRESSURE && tp.z < configs.MAXPRESSURE)) {
        return;
    }

    this->messageManager.sendTSPoint(tp);

    // char buffer[255] = [];
    // this->messageManager.readString(buffer);
    // Serial.println("Received out: " + String(buffer));

    switch (configs.ORIENTATION) {
        case 0:
            xpos = map(tp.x, configs.TS_LEFT, configs.TS_RT, 0, tft->width());
            ypos = map(tp.y, configs.TS_TOP, configs.TS_BOT, 0, tft->height());
            break;
        case 1:
            xpos = map(tp.y, configs.TS_TOP, configs.TS_BOT, 0, tft->width());
            ypos = map(tp.x, configs.TS_RT, configs.TS_LEFT, 0, tft->height());
            break;
        case 2:
            xpos = map(tp.x, configs.TS_RT, configs.TS_LEFT, 0, tft->width());
            ypos = map(tp.y, configs.TS_BOT, configs.TS_TOP, 0, tft->height());
            break;
        case 3:
            xpos = map(tp.y, configs.TS_BOT, configs.TS_TOP, 0, tft->width());
            ypos = map(tp.x, configs.TS_LEFT, configs.TS_RT, 0, tft->height());
            break;
    }

    if (ypos < boxSize) {               //draw configs.white border on selected color box
        oldcolor = currentcolor;

        if (xpos < boxSize) {
            currentcolor = configs.RED;
            tft->drawRect(0, 0, boxSize, boxSize, configs.WHITE);
        } else if (xpos < boxSize * 2) {
            currentcolor = configs.YELLOW;
            tft->drawRect(boxSize, 0, boxSize, boxSize, configs.WHITE);
        } else if (xpos < boxSize * 3) {
            currentcolor = configs.GREEN;
            tft->drawRect(boxSize * 2, 0, boxSize, boxSize, configs.WHITE);
        } else if (xpos < boxSize * 4) {
            currentcolor = configs.CYAN;
            tft->drawRect(boxSize * 3, 0, boxSize, boxSize, configs.WHITE);
        } else if (xpos < boxSize * 5) {
            currentcolor = configs.BLUE;
            tft->drawRect(boxSize * 4, 0, boxSize, boxSize, configs.WHITE);
        } else if (xpos < boxSize * 6) {
            currentcolor = configs.MAGENTA;
            tft->drawRect(boxSize * 5, 0, boxSize, boxSize, configs.WHITE);
        }

        if (oldcolor != currentcolor) { //rub out the previous configs.white border
            if (oldcolor == configs.RED) tft->fillRect(0, 0, boxSize, boxSize, configs.RED);
            if (oldcolor == configs.YELLOW) tft->fillRect(boxSize, 0, boxSize, boxSize, configs.YELLOW);
            if (oldcolor == configs.GREEN) tft->fillRect(boxSize * 2, 0, boxSize, boxSize, configs.GREEN);
            if (oldcolor == configs.CYAN) tft->fillRect(boxSize * 3, 0, boxSize, boxSize, configs.CYAN);
            if (oldcolor == configs.BLUE) tft->fillRect(boxSize * 4, 0, boxSize, boxSize, configs.BLUE);
            if (oldcolor == configs.MAGENTA) tft->fillRect(boxSize * 5, 0, boxSize, boxSize, configs.MAGENTA);
        }
    }

    if (((ypos - PENRADIUS) > boxSize) && ((ypos + PENRADIUS) < tft->height())) {
        tft->fillCircle(xpos, ypos, PENRADIUS, currentcolor);
    }

    if (ypos > tft->height() - 10) {
        // press the bottom of the screen to erase
        tft->fillRect(0, boxSize, tft->width(), tft->height() - boxSize, configs.BLACK);
    }
}

int16_t DrawingScreen::getBoxSize(void) {
  return this->tft->width() / 6;
}