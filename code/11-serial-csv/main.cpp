#include <Arduino.h>

const int LDR_PIN = 9;

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long t = millis();      // 时间戳
  int val = analogRead(LDR_PIN);   // 读数

  // CSV 格式：时间,数值（Python 用 split(",") 拆）
  Serial.print(t);
  Serial.print(",");
  Serial.println(val);

  delay(20);   // 约 50Hz 采样
}
