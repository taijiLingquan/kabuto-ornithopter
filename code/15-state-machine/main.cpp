#include <Arduino.h>

const int LDR_PIN = 9;
const int LED_PIN = 7;
const int BUZZER_PIN = 8;
const int N = 10;
int buf[N];

// 阈值（按实际环境调）
const int ALARM_TH = 100;    // 低于这个 = 完全遮住 → 报警
const int NIGHT_TH = 500;    // 低于这个 = 暗 → 夜灯

enum State { DAY, NIGHT, ALARM };
State state = DAY;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  for (int i = 0; i < N; i++) buf[i] = 0;
}

void loop() {
  // 移动平均
  for (int i = N - 1; i > 0; i--) buf[i] = buf[i - 1];
  buf[0] = analogRead(LDR_PIN);
  long sum = 0;
  for (int i = 0; i < N; i++) sum += buf[i];
  int filtered = sum / N;

  // 状态机（LED 全程用 analogWrite，关=0）
  switch (state) {
    case DAY:
      analogWrite(LED_PIN, 0);
      digitalWrite(BUZZER_PIN, LOW);
      if (filtered < NIGHT_TH) state = NIGHT;
      break;

    case NIGHT:
      analogWrite(LED_PIN, 150);
      digitalWrite(BUZZER_PIN, LOW);
      if (filtered < ALARM_TH) state = ALARM;
      else if (filtered >= NIGHT_TH) state = DAY;
      break;

    case ALARM:
      analogWrite(LED_PIN, 255);
      digitalWrite(BUZZER_PIN, HIGH);
      if (filtered >= ALARM_TH) state = NIGHT;
      break;
  }

  Serial.print(filtered);
  Serial.print(" 状态:");
  Serial.println(state);
  delay(50);
}
