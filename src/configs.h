#include "Arduino.h"

struct {
    const int MINPRESSURE = 200;
    const int MAXPRESSURE = 1000;
    const int BLACK = 0x0000;
    const int BLUE = 0x001F;
    const int RED = 0xF800;
    const int GREEN = 0x07E0;
    const int CYAN = 0x07FF;
    const int MAGENTA = 0xF81F;
    const int YELLOW = 0xFFE0;
    const int WHITE = 0xFFFF;
    const int XP = 8;
    const int XM = A2;
    const int YP = A3;
    const int YM = 9;
    const int TS_LEFT = 127;
    const int TS_RT = 909;
    const int TS_TOP = 954;
    const int TS_BOT = 94;
    const int ORIENTATION = 0;
} configs;
