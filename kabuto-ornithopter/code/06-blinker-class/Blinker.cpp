#include "Blinker.h"

Blinker::Blinker(int pin, unsigned long interval) {
  _pin = pin;
  _interval = interval;
  _state = LOW;
  _previousMillis = 0;
  _brightness = 0;
  _step = 5;
  _prevBreath = 0;
}

void Blinker::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _state);
}

void Blinker::update() {
  unsigned long now = millis();
  if (now - _previousMillis >= _interval) {
    _previousMillis = now;
    _state = !_state;
    digitalWrite(_pin, _state);
  }
}

void Blinker::breathe() {
  if (millis() - _prevBreath < _interval) return;   // interval 当步进间隔
  _prevBreath = millis();
  _brightness += _step;
  if (_brightness >= 255) { _brightness = 255; _step = -5; }
  else if (_brightness <= 0) { _brightness = 0; _step = 5; }
  analogWrite(_pin, _brightness);
}

void Blinker::on()  { _state = HIGH; digitalWrite(_pin, _state); }
void Blinker::off() { _state = LOW;  digitalWrite(_pin, _state); }
void Blinker::toggle() { _state = !_state; digitalWrite(_pin, _state); }
