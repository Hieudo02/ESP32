#include "OTA_AP.h"

OTA_AP _OTA;

void setup() {
  _OTA.OTASetHostname("hieunehihi"); // http://<hostname>.local or IP
  _OTA.OTASetAP("Hieuneee", "123456789");
  _OTA.OTABegin();

  // do sth
}

void loop(void) {
  _OTA.OTAHandle();

  // do sth
} 