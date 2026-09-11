#include <sys/_types.h>

#pragma once

#include <Arduino.h>
#include <sys/_stdint.h>
#include "Config.h"
#include "HardwareMap.h"

class InputManager {
public:
  void begin(uint8_t pin);

  void update();

  void setPin(uint8_t pin);
  uint8_t getPin() const;

  void setDebounceTime(unsigned long timeMS);
  unsigned long getDebounceTime() const;

  bool getRawState() const;
  bool getStableState() const;

  bool isActive() const;
  bool isInactive() const;
private:
  // default configuration
  uint8_t pin = DI_PINS[DigitalInput::DI1];

  bool rawState = HIGH;
  bool stableState = HIGH;

  unsigned long lastChangeTime = 0;
  unsigned long debounceTime = INPUT_DEBOUNCE_MS;
};