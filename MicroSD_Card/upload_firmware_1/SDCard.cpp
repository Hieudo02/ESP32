#include "SDCard.h"

// 3V3	  3.3V
// CS	  GPIO 5
// MOSI	GPIO 23
// CLK	  GPIO 18
// MISO	GPIO 19
// GND	  GND

void progressCallBack(size_t currSize, size_t totalSize) {
  Serial.printf("CALLBACK:  Update process at %d of %d bytes...\n", currSize, totalSize);
}

#define FIRMWARE_VERSION 0.2

void SDCard::SDCardBegin(uint8_t pinChipSelect, String filename) {
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!SD.begin(pinChipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    // while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  Serial.print("Card size:  ");
  Serial.println((float)SD.cardSize() / 1000);

  Serial.print("Total bytes: ");
  Serial.println(SD.totalBytes());

  Serial.print("Used bytes: ");
  Serial.println(SD.usedBytes());

  Serial.print(F("Current firmware version: "));
  Serial.println(FIRMWARE_VERSION);

  
  Serial.println("Searching for " + filename);
  File firmware = SD.open("/" + filename + ".bin");

  if (firmware) {
    Serial.println(F("found!"));
    Serial.println(F("Try to update!"));

    Update.onProgress(progressCallBack);

    Update.begin(firmware.size(), U_FLASH);
    Update.writeStream(firmware);
    if (Update.end()) {
      Serial.println(F("Update finished!"));
    } else {
      Serial.println(F("Update error!"));
      Serial.println(Update.getError());
    }

    firmware.close();

    if (SD.rename("/" + filename + ".bin", "/" + filename + ".bak")) {
      Serial.println(F("Firmware rename succesfully!"));
    } else {
      Serial.println(F("Firmware rename error!"));
    }
    delay(2000);

    ESP.restart();
  } else {
    Serial.println(F("firmware not found!"));
  }

  Serial.print(F("Firmware version "));
  Serial.println(FIRMWARE_VERSION);
}