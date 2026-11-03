#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#define MPU_ADDR 0x68

int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw;
float axOff = 0, ayOff = 0, azOff = 0;
float gxOff = 0, gyOff = 0, gzOff = 0;

float pitch = 0, roll = 0;
const float ALPHA = 0.98;
unsigned long lastTime = 0;

// —— 中值滤波：3 个数取中间值（滤掉单帧尖峰）——
float median3(float a, float b, float c) {
  if ((a <= b && b <= c) || (c <= b && b <= a)) return b;
  if ((b <= a && a <= c) || (c <= a && a <= b)) return a;
  return c;
}

bool readMPU() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  if (Wire.requestFrom(MPU_ADDR, 14) != 14) return false;
  uint8_t d[14];
  for (int i = 0; i < 14; i++) d[i] = Wire.read();
  axRaw = (int16_t)((d[0] << 8) | d[1]);
  ayRaw = (int16_t)((d[2] << 8) | d[3]);
  azRaw = (int16_t)((d[4] << 8) | d[5]);
  gxRaw = (int16_t)((d[8] << 8) | d[9]);
  gyRaw = (int16_t)((d[10] << 8) | d[11]);
  gzRaw = (int16_t)((d[12] << 8) | d[13]);
  return true;
}

void calibrate() {
  long axS = 0, ayS = 0, azS = 0, gxS = 0, gyS = 0, gzS = 0;
  for (int i = 0; i < 300; i++) {
    readMPU();
    axS += axRaw; ayS += ayRaw; azS += azRaw;
    gxS += gxRaw; gyS += gyRaw; gzS += gzRaw;
    delay(5);
  }
  axOff = axS / 300.0;
  ayOff = ayS / 300.0;
  azOff = azS / 300.0 - 16384;
  gxOff = gxS / 300.0;
  gyOff = gyS / 300.0;
  gzOff = gzS / 300.0;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  Serial.println("校准中，请静止...");
  calibrate();
  Serial.println("校准完成");
  lastTime = millis();
}

void loop() {
  if (!readMPU()) { delay(5); return; }

  float ax = axRaw - axOff;
  float ay = ayRaw - ayOff;
  float az = azRaw - azOff;

  float accPitch = atan2(ax, sqrt(ay*ay + az*az)) * 180 / PI;
  float accRoll  = atan2(ay, sqrt(ax*ax + az*az)) * 180 / PI;

  float gyroPitchRate = (gyRaw - gyOff) / 131.0;   // 绕 Y = pitch
  float gyroRollRate  = (gxRaw - gxOff) / 131.0;   // 绕 X = roll

  if (fabs(gyroPitchRate) > 500) gyroPitchRate = 0;
  if (fabs(gyroRollRate) > 500) gyroRollRate = 0;

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;
  if (dt > 0.05) dt = 0.05;
  if (dt < 0.001) dt = 0.001;

  pitch = ALPHA * (pitch + gyroPitchRate * dt) + (1 - ALPHA) * accPitch;
  roll  = ALPHA * (roll  + gyroRollRate  * dt) + (1 - ALPHA) * accRoll;

  static float pH[3] = {0, 0, 0};
  static float rH[3] = {0, 0, 0};
  static int idx = 0;

  pH[idx] = pitch;
  rH[idx] = roll;
  idx = (idx + 1) % 3;

  float pOut = median3(pH[0], pH[1], pH[2]);
  float rOut = median3(rH[0], rH[1], rH[2]);

  Serial.print(pOut, 2);
  Serial.print(",");
  Serial.println(rOut, 2);

  delay(10);
}
