#include <Arduino.h>
#include "Blinker.h"

Blinker led(8, 1000);   // 引脚 8，1 秒闪一次

void setup() {
  led.begin();
}

void loop() {
  led.update();   // 闪烁；想呼吸就改成 led.breathe()
}
