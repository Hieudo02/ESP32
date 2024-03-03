#include "ESPNow2Ways.h"
#include "SDCard.h"

ESPNOW _ESPNow;
SDCard _SDCard;

const int chipSelect = 5;  // SD card

ESPNOW::DuLieuTruyenNhan_t DuLieuGuiDi;

int num = 0;

void setup() {
  Serial.begin(115200);
  _SDCard.SDCardBegin(chipSelect);

  _ESPNow.KhoiTaoESPNow();

  strcpy(DuLieuGuiDi.boardName, "KingOven");
}

void loop() {
  while (Serial.available() > 0) {
    String text = Serial.readString();
    text.trim();  // Loại bỏ các khoảng trắng ở đầu và cuối chuỗi

    if (strstr((char*)text.c_str(), "restart")) {
      ESP.restart();
    } else {
      _SDCard.SDCardUploadFirmware(text);
    }
  }

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
