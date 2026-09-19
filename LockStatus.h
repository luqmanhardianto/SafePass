
#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "esp32-hal-gpio.h"
#include "HardwareMap.h"
#include "InputManager.h"

class LockStatus {
private:
  InputManager input;
public:
  void begin(DigitalInput input);

  void readState();

  bool isLocked() const;
  bool isUnlocked() const;
};