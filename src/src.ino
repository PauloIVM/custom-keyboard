#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "DrawingScreen.h"
#include "CommandsScreen.h"
#include "configs.h"

// TODO: Criar uma classe que abstrai minimamente a comunicação serial com o PC; concatenando bytes e
// transformando em strings, pra que eu possa enviar uma string do PC para mostrar no display.
// TODO: Criar um screens-manager, pra gerenciar a transição de telas.

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(configs.XP, configs.YP, configs.XM, configs.YM, 300);
DrawingScreen ds = DrawingScreen(&tft, &ts);
CommandsScreen cs = CommandsScreen(&tft, &ts);

void setup(void) {
    Serial.begin(9600);
    tft.reset();
    tft.begin(tft.readID());
    tft.setRotation(configs.ORIENTATION);
}

void loop() {
    cs.loadScreen();
    while(cs.showScreen()) {}
    ds.loadScreen();
    delay(1000);
    while(1) {
        ds.showScreen();
    }
}

