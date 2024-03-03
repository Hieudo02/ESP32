- Board không kết nối wifi (A) muốn gửi data sang board có dùng wifi (B) thì cần:
+ Board A đổi channel sang channel mà wifi Board B đang dùng (SSID)
+ Board B cần ở mode AP_STA hoặc mode STA kết hợp hàm "WiFi.setSleep(false);" 