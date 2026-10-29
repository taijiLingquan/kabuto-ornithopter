#include <Arduino.h>

void setup() {
  Serial.begin(115200);   // 打开串口
}

void loop() {
  Serial.println("Hello, Kabuto!");
  delay(1000);
}
