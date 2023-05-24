#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "DrawingScreen.h"
#include "configs.h"

// TODO: Criar uma classe que abstrai minimamente a comunicação serial com o PC; concatenando bytes e
// transformando em strings, pra que eu possa enviar uma string do PC para mostrar no display.

// TODO: Criar um screens-manager, pra gerenciar a transição de telas.

// INFO: Esse ID pode ficar dentro da struct? Testar se ela funciona de maneira
// global, ou se a cada import gera uma cópia;
uint16_t ID;

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(configs.XP, configs.YP, configs.XM, configs.YM, 300);
DrawingScreen ds = DrawingScreen(&tft, &ts);
MessageManager messageManager = MessageManager();
TSPoint tp;
int16_t ht = 16, top = 2, line = 24, lines = 24, scroll;

void showCmdsScreen(void) {
    tft.fillScreen(configs.BLACK);
    tft.setTextSize(2);

    tft.setTextColor(configs.RED);
    tft.println("SHORTCUTS LIST:");
    tft.println();

    tft.setTextColor(configs.YELLOW, configs.BLACK);
    tft.println("- Shortcut 1");
    tft.println("- Shortcut 2");
    tft.println("- Shortcut 3");
    tft.println("- Shortcut 4");
    tft.println("- Shortcut 5");
    tft.println("- Shortcut 6");
    tft.println("- Shortcut 7");
    tft.println("- Shortcut 8");
    tft.println("- Shortcut 9");
    tft.println("- Shortcut 10");
    tft.println("- Shortcut 11");
    tft.println("- Shortcut 12");
    tft.println("- Shortcut 13");
    tft.println("- Shortcut 14");
    tft.println("- Shortcut 15");
    tft.println("- Shortcut 16");
    tft.println("- Shortcut 17");
    tft.println("- Shortcut 18");
    tft.println("- Shortcut 19");
    tft.println("- Shortcut 20");
    tft.println("- Shortcut 21");
    tft.println("- Shortcut 22");
    tft.println("- Shortcut 23");
    tft.println("- Shortcut 24");

    while (1) {
        tp = ts.getPoint();
        pinMode(configs.XM, OUTPUT);
        pinMode(configs.YP, OUTPUT);
        
        char buffer[255] = {0};
        messageManager.readString(buffer);
        // ------------------- Scroll -------------------------
        // u -> 117;
        // d -> 100;
        // enter -> 10
        if (buffer[0] == 117) {
            tft.setCursor(0, (scroll + top) * ht);
            if (++scroll >= lines) scroll = 0;
            tft.vertScroll(top * ht, lines * ht, (scroll) * ht);
            // TODO: Calcular certinho o número de chars que cabem na linha pra preencher com espaços vazios;
            // INFO: Esse println na realidade vai ser a informação vinda do serial...
            line++;
            tft.println("- Shortcut " + String(line) + "   ");
            continue;
        }
        if (buffer[0] == 100) {
            if (line == 24) {
                continue;
            }
            tft.setCursor(0, (scroll + top) * ht);
            if (--scroll >= lines) scroll = 0;
            tft.vertScroll(top * ht, lines * ht, (scroll) * ht);
            line--;
            tft.setCursor(0, (scroll + top) * ht);
            tft.println("- Shortcut " + String(line - 24) + "   ");
            continue;
        }
        // ----------------------------------------------------

        // --------- Escrever o que está no serial ------------
        if (buffer[0] != NULL) {
            // Preciso conseguir jogar o cursor pra última linha...
            // Provavelmetne eu não vou precisar desse cara dentro do while(1), mas apenas
            // antes mesmo. Posso criar uma etapa de load em que fica lendo mensagens da api
            // e enquanto não retornar um código prédefinido não sai dessa etapa. Aí só depois
            // cai aqui.
            tft.print(buffer);
        }
        // ----------------------------------------------------
        if (tp.z < configs.MINPRESSURE || tp.z > configs.MAXPRESSURE) { continue; }
        if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) { break; }
        
        // tft.setCursor(0, (tft.height() * 3) / 4);
        // tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ");
    }
}

void setup(void) {
    Serial.begin(9600);

    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(configs.ORIENTATION);
    if (ID == 0x9320 || ID == 0x9325 || ID == 0xB509) {
        top = 0;                      // these controllers scroll full screen
        lines = tft.height() / ht;    // we are in portrait mode
    }
}

void loop() {
    showCmdsScreen();
    ds.loadScreen();
    delay(1000);
    while(1) {
        ds.showScreen();
        // INFO: Aparentemente esse Serial.available() retorna a quantidade de bytes disponíveis para leitura,
        // então eu posso aguardar a pilha atingeir um determinado size para só então fazer a leitura. Isso deve
        // me ajudar a conseguir enviar strings pro arduino. Aparentemente o limite do buffer é de 64 bytes.
        // INFO: O Serial.read() lê o byte mais recente. Caso não haja nenhum byte nos retorna -1.
        // INFO: Docs interessante: https://embarcados.com.br/arduino-comunicacao-serial/
        // if (Serial.available() > 0) {
        //     char incomingByte = 0;
        //     incomingByte = Serial.read();
        //     Serial.println(incomingByte, DEC);
        //     // INFO: char '1'
        //     if (incomingByte == 49) {
        //       break;
        //     }
        // }
    }
}

