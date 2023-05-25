#include <TouchScreen.h>

class MessageManager {
    public:
        MessageManager(void);
        void send(char *str);
        void sendTSPoint(TSPoint);
        void readString(char buffer[]);
};
