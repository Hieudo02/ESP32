#include "ESPNow2Ways.h"

ESPNOW _ESPNow;

ESPNOW::DuLieuTruyenNhan_t DuLieuGuiDi;

void setup() {
  Serial.begin(115200);
  _ESPNow.KhoiTaoESPNow();

  strcpy(DuLieuGuiDi.boardName, "KingOven");
  DuLieuGuiDi.varBool = true;
}

void loop() {
  _ESPNow.GuiDuLieuQuaESPNow(DuLieuGuiDi);

  if (strcmp(_ESPNow.DuLieuNhanDuoc.boardName, "KingIncu") == 0) {
    Serial.println("OK Incu");
    DuLieuGuiDi.numInt = 14;
  }

  Serial.print("Incoming Data num: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.numInt);
  Serial.print("Incoming Data boardname: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.boardName);
  Serial.print("Incoming Data varBool: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.varBool);
  
  delay(1000);
}
