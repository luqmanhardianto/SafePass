#pragma once

#include <Arduino.h>

#include "HardwareMap.h"
#include "Config.h"

class InputManager {
private:
  uint8_t pin;

  bool lastInputState = HIGH;
  bool stableInputState = HIGH;

  unsigned long lastTimeStateChanged = 0;
  unsigned long debounceTimeMs = INPUT_DEBOUNCE_MS;
public:
  void begin(DigitalInput input);
  void readState();
  bool isActive() const;
};