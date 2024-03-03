#include "ESPNow2Ways.h"
#include "OTA_AP.h"

ESPNOW _ESPNow;
OTA_AP _OTA;

ESPNOW::DuLieuTruyenNhan_t DuLieuGuiDi;

int num = 0;

void setup() {
  Serial.begin(115200);

  // TEST Nhấn giữ boot phát OTA_AP
  pinMode(0, INPUT);

  _ESPNow.KhoiTaoESPNow();

  strcpy(DuLieuGuiDi.boardName, "KingOven");
}

void loop() {
  // TEST Nhấn giữ boot phát OTA_AP
  if (digitalRead(0) == LOW) {
    num++;
    Serial.print("Nhấn giữ: ");
    Serial.println(num);
  }
  if (num == 3) {
    // OTA
    num = 0;
    _OTA.OTASetHostname("hieune"); // http://<hostname>.local
    _OTA.OTASetAP("HieuHapHoi", "123456789");
    _OTA.OTABegin();
  }
  _OTA.OTAHandle();

  _ESPNow.GuiDuLieuQuaESPNow(DuLieuGuiDi);

  if (strcmp(_ESPNow.DuLieuNhanDuoc.boardName, "KingIncu") == 0) {
    Serial.println("OK Incu");
    DuLieuGuiDi.numInt = 14;
  }

  Serial.print("Incoming Data num: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.numInt);
  Serial.print("Incoming Data boardname: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.boardName);

  delay(1000);
}
