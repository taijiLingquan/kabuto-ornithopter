#include <Arduino.h>
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5);   // SDA=GPIO4, SCL=GPIO5
  Serial.println("开始扫描 I2C 设备...");
}

void loop() {
  int found = 0;
  for (int addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {   // 返回 0 = 有设备应答
      Serial.print("发现设备 0x");
      Serial.println(addr, HEX);
      found++;
    }
  }
  if (found == 0) {
    Serial.println("（没发现 I2C 设备）");
  }
  delay(2000);
}
