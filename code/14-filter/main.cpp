#include <Arduino.h>

const int LDR_PIN = 9;
const int N = 10;          // 窗口大小（取最近 N 个平均）
int buf[N];

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < N; i++) buf[i] = 0;
}

void loop() {
  // 后移，丢掉最旧的
  for (int i = N - 1; i > 0; i--) buf[i] = buf[i - 1];
  // 新值放第一位
  buf[0] = analogRead(LDR_PIN);

  // 求平均
  long sum = 0;
  for (int i = 0; i < N; i++) sum += buf[i];
  int filtered = sum / N;

  // 输出：原始值,滤波值
  Serial.print(buf[0]);
  Serial.print(",");
  Serial.println(filtered);

  delay(50);
}
