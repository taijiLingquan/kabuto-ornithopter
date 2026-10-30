#include <Arduino.h>

const int LDR_PIN = 9;    // 光敏模块 S 脚 → GPIO9
const int LED_PIN = 7;    // 外接 LED → GPIO7

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int val = analogRead(LDR_PIN);               // 读光强 0~4095
  int brightness = map(val, 0, 4095, 255, 0);  // 越暗越亮

  if (val < 500) {
    analogWrite(LED_PIN, brightness);          // 夜灯
  } else {
    analogWrite(LED_PIN, 0);
  }

  Serial.println(val);
  delay(50);
}
