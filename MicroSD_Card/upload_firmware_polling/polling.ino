// 3V3	  3.3V
// CS	  GPIO 5
// MOSI	GPIO 23
// CLK	  GPIO 18
// MISO	GPIO 19
// GND	  GND


#include "FS.h"
#include "SD.h"
#include "SPI.h"

void setup() {
  // Initialize the microSD Card
  Serial.begin(115200);
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  /*
  If you don’t pass any argument to the begin() function, 
  it will try to initialize SPI communication with the microSD card on the default chip select (CS) pin. 
  If you want to use another CS pin, you can pass it as an argument to the begin() function. 
  For example, if you wanted to use GPIO 17 as a CS pin, you should use the following lines of code:
  
  Serial.begin(115200);
  if(!SD.begin(17)){
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  */

  // Get microSD Card Type
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  // Get microSD Card Size
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}