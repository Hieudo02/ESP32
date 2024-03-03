#ifndef ESPNOW_2WAYS_H
#define ESPNOW_2WAYS_H

#include <esp_now.h>
#include <esp_wifi.h>
#include <String>
#include <WiFi.h>

class ESPNOW {
public:
  typedef struct struct_message {
    char boardName[32];
    int numInt;
    float numFloat;
    bool varBool;
    uint8_t testnum;
  } DuLieuTruyenNhan_t;
  static DuLieuTruyenNhan_t DuLieuNhanDuoc;

  static String WIFI_SSID;
  int32_t channel;
  
  void KhoiTaoESPNow();
  void setupWiFiChannel(String _ssid);
  void GuiDuLieuQuaESPNow(const DuLieuTruyenNhan_t &myData);

private:
  static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
  static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

};

#endif