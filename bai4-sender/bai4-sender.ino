#include <WiFi.h>
#include <esp_now.h>

// --- THAY MAC CỦA RECEIVER VÀO ĐÂY ---
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xA1, 0xB2, 0xC3};

typedef struct struct_message {
  int bootCount;
  float temp;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

// Biến lưu trong bộ nhớ RTC (không mất khi ngủ)
RTC_DATA_ATTR int bootCount = 0;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Trạng thái gửi: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành công" : "Thất bại");
}

void setup() {
  Serial.begin(115200);
  
  // Tăng biến đếm số lần thức dậy
  bootCount++;
  Serial.println("---------------------------------");
  Serial.print("Lần thức dậy thứ: ");
  Serial.println(bootCount);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Lỗi ESP-NOW");
    return;
  }

  esp_now_register_send_cb((esp_now_send_cb_t)OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Lỗi thêm Peer");
    return;
  }

  // Chuẩn bị dữ liệu
  myData.bootCount = bootCount;
  myData.temp = 25.0 + random(0, 50)/10.0;

  // Gửi dữ liệu
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  
  // Chờ dữ liệu bay đi hết (quan trọng trước khi ngủ)
  delay(100); 

  // Cài đặt ngủ 5 giây (5 * 1.000.000 microseconds)
  esp_sleep_enable_timer_wakeup(5 * 1000000);
  
  Serial.println("Đang ngủ đông (Deep Sleep)...");
  Serial.flush(); 
  
  // Bắt đầu ngủ
  esp_deep_sleep_start();
}

void loop() {
}