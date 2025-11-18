#include <WiFi.h>
#include <esp_now.h>

typedef struct struct_message {
    int bootCount;
    float temp;
} struct_message;

struct_message myData;

void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  
  Serial.print("Nhận lần thứ: ");
  Serial.println(myData.bootCount);
  Serial.print("Nhiệt độ: ");
  Serial.println(myData.temp);
  Serial.println("-----------------------");
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) return;
  
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  
}