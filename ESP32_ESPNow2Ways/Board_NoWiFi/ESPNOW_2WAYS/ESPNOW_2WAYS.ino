#include "ESPNow2Ways.h"

ESPNOW _ESPNow;

ESPNOW::DuLieuTruyenNhan_t DuLieuGuiDi;
String SSID = "IoTVision_2.4GHz";

void setup() {
  Serial.begin(115200);
  _ESPNow.setupWiFiChannel("IoTVision_2.4GHz");
  _ESPNow.KhoiTaoESPNow();

  strcpy(DuLieuGuiDi.boardName, "KingIncu");
  DuLieuGuiDi.varBool = true;
}

void loop() {
  Serial.print("Channel: ");
  Serial.println(_ESPNow.channel);

  _ESPNow.GuiDuLieuQuaESPNow(DuLieuGuiDi);

  if (strcmp(_ESPNow.DuLieuNhanDuoc.boardName, "KingOven") == 0) {
    Serial.println("OK Oven");
    DuLieuGuiDi.numInt = 13;
  }

  Serial.print("Incoming Data num: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.numInt);
  Serial.print("Incoming Data boardname: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.boardName);
  Serial.print("Incoming Data varBool: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.varBool);

  delay(1000);
}
