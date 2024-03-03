#ifndef _ESPNOW_h
#define _ESPNOW_h

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

class ESPNOW {
public:
  void KhoiTao(void);

  static struct DuLieuNhan {
    char charArr[32];
    int numInt;
    float numFloat;
    bool varBool;
  } DuLieuNhanDuoc;

private:
  static void NhanDuLieuQuaESPNow(const uint8_t *mac, const uint8_t *incomingData, int len);
};

#endif

/*
void* memcpy(void* destination, const void* source, size_t numBytes);

destination: A pointer to the memory location where the copied data will be stored.
source: A pointer to the memory location from which the data is to be copied.
numBytes: The number of bytes to be copied.
*/
