#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#define MPU_ADDR 0x68

int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw;
float axOff = 0, ayOff = 0, azOff = 0;

void readMPU() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14);
  uint8_t d[14];
  for (int i = 0; i < 14; i++) d[i] = Wire.read();
  axRaw = (d[0] << 8) | d[1];
  ayRaw = (d[2] << 8) | d[3];
  azRaw = (d[4] << 8) | d[5];
  gxRaw = (d[8] << 8) | d[9];
  gyRaw = (d[10] << 8) | d[11];
  gzRaw = (d[12] << 8) | d[13];
}

void calibrate() {
  long axSum = 0, aySum = 0, azSum = 0;
  for (int i = 0; i < 200; i++) {
    readMPU();
    axSum += axRaw;
    aySum += ayRaw;
    azSum += azRaw;
    delay(5);
  }
  axOff = axSum / 200.0;
  ayOff = aySum / 200.0;
  azOff = azSum / 200.0 - 16384;   // 减去 1g
}

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  Serial.println("校准中，请保持板子静止...");
  calibrate();
  Serial.println("校准完成");
}

void loop() {
  readMPU();

  float ax = axRaw - axOff;
  float ay = ayRaw - ayOff;
  float az = azRaw - azOff;

  // 加速度计求角度（弧度转度）
  float pitch = atan2(ax, sqrt(ay*ay + az*az)) * 180 / PI;
  float roll  = atan2(ay, sqrt(ax*ax + az*az)) * 180 / PI;

  Serial.print(pitch, 1);
  Serial.print(",");
  Serial.println(roll, 1);

  delay(100);
}
