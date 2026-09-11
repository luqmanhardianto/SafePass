#pragma once

#include <Arduino.h>
#include <sys/_stdint.h>

#include "Config.h"
#include "HardwareMap.h"

class PushButton {
private:
  uint8_t pin;

  bool lastButtonState = HIGH;
  bool stableButtonState = HIGH;



  unsigned long lastTimeStateChanged = 0;
  unsigned long debounceTimeMs = INPUT_DEBOUNCE_MS;
public:
  void begin(DigitalInput input);

  void readState();

  bool isPressed() const;

  uint8_t getPin() const;
};