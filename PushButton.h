
#pragma once

#include <Arduino.h>
#include "InputManager.h"
#include <sys/_stdint.h>

class PushButton {
public:
  void begin(uint8_t pin);

  void update();

  uint8_t getPin() const;

  bool getState() const;
  bool isPressed() const;
  bool isReleased() const;
private:
  InputManager input;

  bool state = HIGH;
};