#include <Arduino.h>

const int BUZZER_PIN = 9;   // 蜂鸣器模块 S 脚接 GPIO9

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // S = 3 短
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);
  }
  delay(600);   // 字母间停顿

  // O = 3 长
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(800);
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);
  }
  delay(600);

  // S = 3 短
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);
  }
  delay(2000);  // 整段间隔
}
