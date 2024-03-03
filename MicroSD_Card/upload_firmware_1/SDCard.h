#include <SPI.h>
#include <Update.h>
#include <SD.h>
#include <String>

class SDCard {
public:
  void SDCardBegin(uint8_t pinChipSelect, String filename);
};