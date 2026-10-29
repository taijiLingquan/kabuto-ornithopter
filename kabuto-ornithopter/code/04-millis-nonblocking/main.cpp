#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define RGB_PIN 21
#define NUMPIXELS 1
const int LED_PIN = 8;

Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_RGB + NEO_KHZ800);

// 定时器 1：外接灯（1 秒）
int ledState = LOW;
unsigned long prevLed = 0;
const long intervalLed = 1000;

// 定时器 2：彩灯（0.5 秒）
int color = 0;
unsigned long prevRgb = 0;
const long intervalRgb = 500;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pixels.begin();
}

void loop() {
  unsigned long now = millis();

  if (now - prevLed >= intervalLed) {
    prevLed = now;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }

  if (now - prevRgb >= intervalRgb) {
    prevRgb = now;
    color = color + 1;
    if (color > 2) color = 0;
    if (color == 0) pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    else if (color == 1) pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    else pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.show();
  }
}
