#include "MessageManager.h"
#include <TouchScreen.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <string.h>

MessageManager::MessageManager() {}

void MessageManager::send(char *str) {}

void MessageManager::sendTSPoint(TSPoint tp) {
  Serial.println("Z: " + String(tp.z) + " X: " + String(tp.x) + " Y: " + String(tp.y));
}

void MessageManager::readString(char buffer[]) {
    int size = Serial.available();
    for (int i = 0; i < size; i++) {
        buffer[i] = Serial.read();
    }
}
