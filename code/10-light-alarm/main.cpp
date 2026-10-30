#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define RGB_PIN 21
#define NUMPIXELS 1
const int LDR_PIN = 9;
const int LED_PIN = 7;
const int BUZZER_PIN = 8;

Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  pixels.begin();
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int val = analogRead(LDR_PIN);

  if (val < 100) {                        // 完全遮住 → 报警
    digitalWrite(BUZZER_PIN, HIGH);
    analogWrite(LED_PIN, 255);
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));  // 红
    pixels.show();
  } else if (val < 500) {                 // 暗 → 夜灯
    int brightness = map(val, 0, 4095, 255, 0);
    analogWrite(LED_PIN, brightness);
    digitalWrite(BUZZER_PIN, LOW);
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));  // 绿
    pixels.show();
  } else {                                // 亮 → 全关
    digitalWrite(BUZZER_PIN, LOW);
    analogWrite(LED_PIN, 0);
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));  // 蓝
    pixels.show();
  }

  Serial.println(val);
  delay(50);
}
