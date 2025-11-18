#include <WiFi.h>
#include <esp_now.h>

typedef struct struct_message {
    char cmd[32];
    int value;
} struct_message;

struct_message myData;

void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  
  Serial.print("Lệnh nhận được: ");
  Serial.print(myData.cmd);
  Serial.print(" | Giá trị: ");
  Serial.println(myData.value);

  // Điều khiển LED (nếu board bạn có LED ở chân 2)
  pinMode(2, OUTPUT);
  if (myData.value == 1) digitalWrite(2, HIGH);
  else digitalWrite(2, LOW);
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) return;
  
  // Đăng ký callback nhận
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}