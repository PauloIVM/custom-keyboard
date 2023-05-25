#include "CommandsScreen.h"
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "Arduino.h"
#include "pins_arduino.h"
#include "configs.h"

CommandsScreen::CommandsScreen(MCUFRIEND_kbv *tft, TouchScreen *ts) {
    this->tft = tft;
    this->ts = ts;
    this->ht = 16;
    this->top = 2;
    this->line = 24;
    this->lines = 24;
    this->scroll = 0;

    // TODO: Se o messageManager for interno às telas, preciso pensar em como
    // conseguir fazer o switch de telas por ele, pra que eu consiga fazer com
    // que o listenner certo ouça a mensagem. Posso criar um pattern observer
    // no messageManager pra bindar o ouvinte certo de cada mensagem.
    this->messageManager = MessageManager();
}

void CommandsScreen::loadScreen(void) {
    this->tft->fillScreen(configs.BLACK);
    this->tft->setTextSize(2);
    this->tft->setTextColor(configs.RED);
    this->tft->println("SHORTCUTS LIST:");
    this->tft->println();
    this->tft->setTextColor(configs.YELLOW, configs.BLACK);
    this->tft->println("- Shortcut 1");
    this->tft->println("- Shortcut 2");
    this->tft->println("- Shortcut 3");
    this->tft->println("- Shortcut 4");
    this->tft->println("- Shortcut 5");
    this->tft->println("- Shortcut 6");
    this->tft->println("- Shortcut 7");
    this->tft->println("- Shortcut 8");
    this->tft->println("- Shortcut 9");
    this->tft->println("- Shortcut 10");
    this->tft->println("- Shortcut 11");
    this->tft->println("- Shortcut 12");
    this->tft->println("- Shortcut 13");
    this->tft->println("- Shortcut 14");
    this->tft->println("- Shortcut 15");
    this->tft->println("- Shortcut 16");
    this->tft->println("- Shortcut 17");
    this->tft->println("- Shortcut 18");
    this->tft->println("- Shortcut 19");
    this->tft->println("- Shortcut 20");
    this->tft->println("- Shortcut 21");
    this->tft->println("- Shortcut 22");
    this->tft->println("- Shortcut 23");
    this->tft->println("- Shortcut 24");
}

int CommandsScreen::showScreen() {
    TSPoint tp = this->ts->getPoint();
    pinMode(configs.XM, OUTPUT);
    pinMode(configs.YP, OUTPUT);
    
    char buffer[255] = {0};
    this->messageManager.readString(buffer);

    if (buffer[0] == 117) {
        this->tft->setCursor(0, (scroll + top) * ht);
        if (++scroll >= lines) scroll = 0;
        this->tft->vertScroll(top * ht, lines * ht, (scroll) * ht);
        // TODO: Calcular certinho o número de chars que cabem na linha pra preencher com espaços vazios;
        // INFO: Esse println na realidade vai ser a informação vinda do serial...
        line++;
        this->tft->println("- Shortcut " + String(line) + "   ");
        return 1;
    }
    if (buffer[0] == 100) {
        if (line == 24) {
            return 1;
        }
        this->tft->setCursor(0, (scroll + top) * ht);
        if (--scroll >= lines) scroll = 0;
        this->tft->vertScroll(top * ht, lines * ht, (scroll) * ht);
        line--;
        this->tft->setCursor(0, (scroll + top) * ht);
        this->tft->println("- Shortcut " + String(line - 24) + "   ");
        return 1;
    }

    if (buffer[0] != NULL) { this->tft->print(buffer); }
    if (tp.z < configs.MINPRESSURE || tp.z > configs.MAXPRESSURE) { return 1; }
    if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) {
        this->tft->vertScroll(top * ht, lines * ht, 0);
        return 0;
    }
}
