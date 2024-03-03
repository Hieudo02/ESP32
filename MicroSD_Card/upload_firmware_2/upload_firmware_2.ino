#include "SDCard.h"

SDCard _SDCard;

const int chipSelect = 5;

void setup() {
  Serial.begin(115200);
  _SDCard.SDCardBegin(chipSelect);
  pinMode(2, OUTPUT);
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
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  delay(100);
}
