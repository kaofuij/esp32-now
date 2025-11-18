#include <WiFi.h>    // Luôn để WiFi.h lên đầu
#include <esp_now.h>

// Thay MAC của Receiver vào đây (Nhớ thêm 0x)
uint8_t broadcastAddress[] = {0x20, 0xE7, 0xC8, 0x67, 0x16, 0x88};

typedef struct struct_message {
  char a[32];
  int b;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

// Hàm Callback gửi
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Trạng thái gửi: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành công" : "Thất bại");
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Lỗi khởi tạo ESP-NOW");
    return;
  }

  // --- SỬA LỖI TẠI ĐÂY: Ép kiểu (cast) hàm callback ---
  esp_now_register_send_cb((esp_now_send_cb_t)OnDataSent);
  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Thêm peer thất bại");
    return;
  }
}
 
void loop() {
  strcpy(myData.a, "Hello ESP32");
  myData.b = random(1, 100);
  
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Đã gửi lệnh đi");
  }
  else {
    Serial.println("Lỗi gửi");
  }
  delay(2000);
}