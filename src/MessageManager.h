#include <TouchScreen.h>
#include <string.h>

class MessageManager {
    public:
        MessageManager();
        void send(char *str);
        void sendTSPoint(TSPoint);
        void readString(char buffer[]);
};