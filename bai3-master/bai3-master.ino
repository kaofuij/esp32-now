#include <WiFi.h>
#include <esp_now.h>

// Địa chỉ BROADCAST (Gửi cho tất cả)
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct struct_message {
  char cmd[32]; 
  int value;    
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

// Hàm callback gửi
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Trạng thái Broadcast: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành công" : "Thất bại");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Lỗi khởi tạo ESP-NOW");
    return;
  }

  
  esp_now_register_send_cb((esp_now_send_cb_t)OnDataSent);
  
  // Đăng ký Peer Broadcast
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Thêm peer thất bại");
    return;
  }
}

void loop() {
  // Gửi lệnh BẬT
  strcpy(myData.cmd, "LED_ON");
  myData.value = 1; 
  Serial.println("Gửi lệnh: BẬT ĐÈN");
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(2000);
  
  // Gửi lệnh TẮT
  strcpy(myData.cmd, "LED_OFF");
  myData.value = 0;
  Serial.println("Gửi lệnh: TẮT ĐÈN");
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(2000);
}