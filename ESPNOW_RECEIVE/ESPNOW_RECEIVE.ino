// Board Phụ - Receiver

#include "ESPNOW.h"

ESPNOW _ESPNow;

void setup() {
  _ESPNow.KhoiTao();
}

void loop() {
  Serial.print("Char: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.charArr);
  Serial.print("Int: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.numInt);
  Serial.print("Float: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.numFloat);
  Serial.print("Bool: ");
  Serial.println(_ESPNow.DuLieuNhanDuoc.varBool);

  delay(1000);
}
