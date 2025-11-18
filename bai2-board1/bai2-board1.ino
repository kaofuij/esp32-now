#include <WiFi.h>
#include <esp_now.h>

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Cấu trúc dữ liệu
typedef struct struct_message {
  int id;       
  float temp;   
  float hum;    
} struct_message;

struct_message myData;        // Dữ liệu gửi
struct_message incomingReadings; // Dữ liệu nhận

esp_now_peer_info_t peerInfo;

// --- 1. Hàm Callback GỬI (Giữ nguyên) ---
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nTrạng thái gửi: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành công" : "Thất bại");
}

// --- 2. Hàm Callback NHẬN (Đã sửa tham số đầu tiên) ---
void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  
  Serial.print("Nhận từ ID: ");
  Serial.println(incomingReadings.id);
  Serial.print("Nhiệt độ: ");
  Serial.println(incomingReadings.temp);
  Serial.print("Độ ẩm: ");
  Serial.println(incomingReadings.hum);
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Lỗi khởi tạo ESP-NOW");
    return;
  }

  // --- SỬA LỖI 1: Ép kiểu cho hàm gửi ---
  esp_now_register_send_cb((esp_now_send_cb_t)OnDataSent);
  
  // --- SỬA LỖI 2: Hàm nhận đã tự động khớp với tham số mới ở trên ---
  esp_now_register_recv_cb(OnDataRecv);

  // Đăng ký Peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Thêm peer thất bại");
    return;
  }
}
 
void loop() {
  myData.id = 1; 
  myData.temp = random(20, 40) + (random(0,100)/100.0);
  myData.hum = random(40, 90) + (random(0,100)/100.0);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result != ESP_OK) {
    Serial.println("Lỗi gửi dữ liệu");
  }
  
  delay(2000);
}