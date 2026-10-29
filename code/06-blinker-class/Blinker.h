#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>

class Blinker {
  private:
    int _pin;
    bool _state;
    unsigned long _previousMillis;
    unsigned long _interval;

    // 呼吸模式成员
    int _brightness;
    int _step;
    unsigned long _prevBreath;

  public:
    Blinker(int pin, unsigned long interval);
    void begin();
    void update();     // 闪烁模式
    void breathe();    // 呼吸模式
    void on();
    void off();
    void toggle();
};

#endif
