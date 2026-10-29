#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define RGB_PIN 21
#define NUMPIXELS 1
const int LED_PIN = 8;   // 外接 LED

// 注意：这颗板载灯是 RGB 顺序，用 NEO_RGB（不是 NEO_GRB）
Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // 红
  pixels.show();
  digitalWrite(LED_PIN, HIGH);
  delay(1000);

  pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // 绿
  pixels.show();
  digitalWrite(LED_PIN, LOW);
  delay(1000);

  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // 蓝
  pixels.show();
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
