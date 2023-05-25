#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
// #include "MessageManager.h"

class DrawingScreen {
    public:
        DrawingScreen(MCUFRIEND_kbv *tft, TouchScreen *ts);
        void loadScreen(void);
        void showScreen(void);
    private:
        int16_t getBoxSize(void);
        MCUFRIEND_kbv *tft;
        TouchScreen *ts;
        // MessageManager messageManager;
        uint16_t oldcolor, currentcolor;
};
