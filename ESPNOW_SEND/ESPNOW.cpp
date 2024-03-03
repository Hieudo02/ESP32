#include "esp_now.h"
#include "ESPNOW.h"

#define _ChanBuzzer 2

#pragma region Test phần ESPNow và WiFi cùng lúc
#ifdef TestESPNow_WiFi
constexpr char WIFI_SSID[] = "YOUR_WIFI_SSID";

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
#endif
#pragma endregion Test phần ESPNow và WiFi cùng lúc

void ESPNOW::KhoiTao(void) {
  Serial.begin(115200);

  // pinMode(_ChanBuzzer, OUTPUT);

  WiFi.mode(WIFI_STA);

#ifdef TestESPNow_WiFi
  int32_t channel = getWiFiChannel(WIFI_SSID);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
#endif

  if (esp_now_init() != ESP_OK) {
    Serial.println("Lỗi khởi tạo ESPNow !");
  } else {
    Serial.println("Khởi tạo ESPNow thành công !");
  }

  // Ký hàm TrangThaiGuiGoiTinCuaBoardMain
  esp_now_register_send_cb(ESPNOW::TrangThaiGuiGoiTinCuaBoardMain);

  // Thêm thiết bị ghép đôi
  peerInfo.channel = 0;      // Kênh wifi mà thiết bị ghép cặp dùng để truyền nhận data. 0: dùng kênh hiện tại của mode STA hoặc SoftAP
  peerInfo.encrypt = false;  // Không mã hóa
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Thêm thiết bị ghép đôi thất bại !");
  } else {
    Serial.println("Thêm thiết bị ghép đôi thành công !");
  }
}

void ESPNOW::TrangThaiGuiGoiTinCuaBoardMain(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Trạng thái của gói tin: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành Công !" : "Thất Bại !");
}
 
void ESPNOW::GuiDuLieuQuaESPNOW(const DuLieuGui_t &data, uint8_t MACCuaBoardNhan[]) {
  esp_err_t result = esp_now_send(MACCuaBoardNhan, (uint8_t *)&data, sizeof(data));

  if (result == ESP_OK) {
    Serial.println("Gửi dữ liệu thành công !");
  } else {
    Serial.println("Gửi dữ liệu thất bại !");
  }
  // delay(500);
}

void ESPNOW::SetMACBoardNhan(const uint8_t *targetMAC) {
  memcpy(peerInfo.peer_addr, targetMAC, 6);
}
