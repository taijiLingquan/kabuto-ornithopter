#include <Arduino.h>

const int BTN_PIN = 2;
volatile bool pressed = false;

void onPress() {
  pressed = true;   // ISR：只设标志，不能 delay/print
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), onPress, FALLING);
}

void loop() {
  static int count = 0;
  static bool locked = false;

  if (pressed) {
    pressed = false;
    if (!locked) {              // 按下锁住，松开解锁（防抖动）
      locked = true;
      count++;
      Serial.println(count);
    }
  }

  if (digitalRead(BTN_PIN) == HIGH) {
    locked = false;             // 松开才解锁
  }
  delay(10);
}
