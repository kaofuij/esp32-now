#include <esp_now.h>
#include <WiFi.h>

// Struct dữ liệu
typedef struct struct_message {
    char a[32];
    int b;
} struct_message;

struct_message myData;

// --- SỬA Ở ĐÂY: Thay đổi tham số đầu tiên ---
void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t *incomingData, int len) {
  
  // Nếu muốn lấy địa chỉ MAC người gửi, dùng: info->src_addr
  // Serial.print("Nhan tu MAC: ");
  // for (int i = 0; i < 6; i++) Serial.print(info->src_addr[i], HEX);

  memcpy(&myData, incomingData, sizeof(myData));
  
  Serial.println("--- Dữ liệu nhận được! ---");
  Serial.print("Dữ liệu Char: ");
  Serial.println(myData.a);
  Serial.print("Dữ liệu Int: ");
  Serial.println(myData.b);
  Serial.println("--------------------------\n");
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Lỗi khởi tạo ESP-NOW");
    return;
  }
  
  // Đăng ký hàm callback
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
}