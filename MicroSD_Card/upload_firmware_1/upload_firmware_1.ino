#include "SDCard.h"

SDCard _SDCard;

const int chipSelect = 5;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String text = Serial.readString(); 
    text.trim(); // Loại bỏ các khoảng trắng ở đầu và cuối chuỗi
    _SDCard.SDCardBegin(chipSelect, text);

    if(strstr((char*)text.c_str(), "restart")) {
      ESP.restart();
    }
  }
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  delay(100);
}
