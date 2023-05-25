#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "MessageManager.h"

class CommandsScreen {
    public:
        CommandsScreen(MCUFRIEND_kbv *tft, TouchScreen *ts);
        void loadScreen(void);
        int showScreen(void);
    private:
        MCUFRIEND_kbv *tft;
        TouchScreen *ts;
        MessageManager messageManager;
        int16_t ht;
        int16_t top;
        int16_t line;
        int16_t lines;
        int16_t scroll;
};
