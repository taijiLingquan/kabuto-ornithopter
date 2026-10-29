#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define RGB_PIN 21
#define NUMPIXELS 1
const int LED_PIN = 8;
String cmd = "";

Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(1000);   // 等 USB 枚举稳定
  pixels.begin();
  pinMode(LED_PIN, OUTPUT);
  Serial.println("命令：on / off / red / green / blue");
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') {
      cmd.trim();
      if (cmd == "on") {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("> ON");
      } else if (cmd == "off") {
        digitalWrite(LED_PIN, LOW);
        Serial.println("> OFF");
      } else if (cmd == "red") {
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.show();
        Serial.println("> RED");
      } else if (cmd == "green") {
        pixels.setPixelColor(0, pixels.Color(0, 255, 0));
        pixels.show();
        Serial.println("> GREEN");
      } else if (cmd == "blue") {
        pixels.setPixelColor(0, pixels.Color(0, 0, 255));
        pixels.show();
        Serial.println("> BLUE");
      }
      cmd = "";
    } else if (c != '\r') {
      cmd += c;
    }
  }
}
