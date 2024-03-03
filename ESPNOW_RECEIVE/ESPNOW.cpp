#include "ESPNOW.h"

#define _ChanBuzzer 2

ESPNOW::DuLieuNhan ESPNOW::DuLieuNhanDuoc; // Khai báo vùng nhớ cho static DuLieuNhanDuoc

void ESPNOW::KhoiTao(void) {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Lỗi khởi tạo ESPNow !");
    return;
  }

  // Ký hàm NhanDuLieuQuaESPNow
  esp_now_register_recv_cb(ESPNOW::NhanDuLieuQuaESPNow);
}

// Hàm callback nhận data
void ESPNOW::NhanDuLieuQuaESPNow(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&DuLieuNhanDuoc, incomingData, sizeof(DuLieuNhanDuoc));
  // Serial.print("Bytes received: ");
  // Serial.println(len);

  // Serial.print("Char: ");
  // Serial.println(DuLieuNhanDuoc.charArr);
  // Serial.print("Int: ");
  // Serial.println(DuLieuNhanDuoc.numInt);
  // Serial.print("Float: ");
  // Serial.println(DuLieuNhanDuoc.numFloat);
  // Serial.print("Bool: ");
  // Serial.println(DuLieuNhanDuoc.varBool);
  // Serial.println();
}
