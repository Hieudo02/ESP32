// Board Main - Sender

#include <Arduino.h>
#include "ESPNOW.h"

ESPNOW _ESPNow; 

// uint8_t MACBoardNhan[] = {0x08, 0xB6, 0x1F, 0x72, 0x6A, 0xD4};
// 08:B6:1F:72:6A:D4 (KitESP32 - Hieu)

// ALL
uint8_t MACBoardNhan[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Data cần gửi đi
ESPNOW::DuLieuGui customData;

void setup() {
  // Set MAC board nhận trước khi khởi tạo
  _ESPNow.SetMACBoardNhan(MACBoardNhan);
  _ESPNow.KhoiTao();
}
 
void loop() {
  strcpy(customData.charArr, "CUSTOM DATA");
  customData.numInt = 37;
  customData.numFloat = 3.14;
  customData.varBool = true;

  _ESPNow.GuiDuLieuQuaESPNOW(customData, MACBoardNhan);
  delay(1000);
}