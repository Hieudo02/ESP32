#include "ESPNOW2Ways.h"

uint8_t broadcastAddress[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
esp_now_peer_info_t peerInfo;

ESPNOW::DuLieuTruyenNhan_t ESPNOW::DuLieuNhanDuoc;
String ESPNOW::WIFI_SSID;

int32_t getWiFiChannel(const char *ssid) {
  if (int32_t n = WiFi.scanNetworks()) {
    for (uint8_t i = 0; i < n; i++) {
      if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
        return WiFi.channel(i);
      }
    }
  }
  return 0;
}

void ESPNOW::setupWiFiChannel(String _ssid) {
  ESPNOW::WIFI_SSID = _ssid;
}

void ESPNOW::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void ESPNOW::OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&DuLieuNhanDuoc, incomingData, sizeof(DuLieuNhanDuoc));

  // Serial.print("Incoming Data num: ");
  // Serial.println(DuLieuNhanDuoc.numInt);
}

void ESPNOW::KhoiTaoESPNow() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  channel = getWiFiChannel(WIFI_SSID.c_str());

  WiFi.printDiag(Serial);  // Uncomment to verify channel number before
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  WiFi.printDiag(Serial);  // Uncomment to verify channel change after

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
  }

  esp_now_register_send_cb(ESPNOW::OnDataSent);
  esp_now_register_recv_cb(ESPNOW::OnDataRecv);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
  }
}

void ESPNOW::GuiDuLieuQuaESPNow(const DuLieuTruyenNhan_t &myData) {
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Send data successful !");
  } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
    Serial.println("ESPNOW not Init.");
  } else if (result == ESP_ERR_ESPNOW_ARG) {
    Serial.println("Invalid Argument");
  } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
    Serial.println("Internal Error");
  } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
    Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
    Serial.println("Peer not found.");
  } else {
    Serial.println("Unknown error");
  }
}
