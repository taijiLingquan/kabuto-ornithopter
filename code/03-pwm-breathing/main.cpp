#include <Arduino.h>

const int LED_PIN = 8;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // 从暗到亮
  for (int b = 0; b <= 255; b++) {
    analogWrite(LED_PIN, b);
    delay(10);
  }
  // 从亮到暗
  for (int b = 255; b >= 0; b--) {
    analogWrite(LED_PIN, b);
    delay(10);
  }
}
