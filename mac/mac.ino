#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  
  // Chờ 1 chút để ổn định nguồn
  delay(1000); 

  // Bật chế độ Station
  WiFi.mode(WIFI_STA);
  
  delay(100); 

  Serial.println();
  Serial.print("Địa chỉ MAC là: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
}