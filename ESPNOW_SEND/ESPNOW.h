#ifndef _ESPNOW_h
#define _ESPNOW_h

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

class ESPNOW {
public:
  typedef struct DuLieuGui {
    char charArr[32];
    int numInt;
    float numFloat;
    bool varBool;
  } DuLieuGui_t;

  void KhoiTao(void);
  void GuiDuLieuQuaESPNOW(const DuLieuGui_t &data, uint8_t MACCuaBoardNhan[]);
  void SetMACBoardNhan(const uint8_t *targetMAC);

private:
  esp_now_peer_info_t peerInfo;
  static void TrangThaiGuiGoiTinCuaBoardMain(const uint8_t *mac_addr, esp_now_send_status_t status);
};

#endif