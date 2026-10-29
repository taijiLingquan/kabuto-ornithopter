#include <Arduino.h>

const int BTN_PIN = 2;
const int LED_PIN = 8;

bool ledOn = false;
bool lastReading = HIGH;
bool btnState = HIGH;
unsigned long lastDebounce = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  bool reading = digitalRead(BTN_PIN);
  if (reading != lastReading) lastDebounce = millis();

  if (millis() - lastDebounce > 50) {   // 消抖 50ms
    if (reading != btnState) {
      btnState = reading;
      if (btnState == LOW) {            // 按下
        ledOn = !ledOn;
        digitalWrite(LED_PIN, ledOn);
        Serial.println(ledOn ? "灯开" : "灯关");
      }
    }
  }
  lastReading = reading;
}
